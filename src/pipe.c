#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

pid_t	fork_and_exec(t_cmd *cmd, t_pipe_ctx *ctx, int i, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_pipes(ctx->pipefds, i, ctx->num_cmds);
		close_all_pipes(ctx->pipefds, 2 * (ctx->num_cmds - 1));
		if (cmd->redirs && apply_redirections_child(cmd, data) != 0)
			exit(1);
		if (is_builtin_name(cmd->argv[0]))
			exit(handle_builtin(cmd->argv, ctx->data));
		exec_child_command(cmd, ctx->data);
		perror("exec");
		exit(127);
	}
	return (pid);
}

static int	fork_pipeline(t_cmd *cmds, t_pipe_ctx *ctx, pid_t *pids,
		t_data *data)
{
	t_cmd	*cur;
	int		i;

	if (ctx->num_cmds > 1)
	{
		if (create_pipes_for_ctx(ctx) != 0)
			return (-1);
	}
	cur = cmds;
	i = 0;
	while (cur)
	{
		pids[i] = fork_and_exec(cur, ctx, i, data);
		if (pids[i] < 0)
			return (-1);
		cur = cur->next;
		i++;
	}
	return (0);
}

static int	init_pipeline_ctx(t_cmd *cmds, t_data *data,
		t_pipe_ctx *ctx, pid_t **pids)
{
	int			num_cmds;
	int			*pipefds;

	if (!ctx || !pids)
		return (1);
	num_cmds = count_cmds(cmds);
	ctx->num_cmds = num_cmds;
	ctx->data = data;
	ctx->pipefds = NULL;
	*pids = NULL;
	if (num_cmds <= 0)
		return (0);
	pipefds = malloc(sizeof(int) * 2 * (num_cmds - 1));
	if (!pipefds)
		return (perror("malloc"), 1);
	*pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
	{
		free(pipefds);
		return (perror("malloc"), 1);
	}
	ctx->pipefds = pipefds;
	return (0);
}

static int	wait_and_cleanup(t_cmd *cmds, t_data *data, t_pipe_ctx *ctx,
			pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	close_all_pipes(ctx->pipefds, 2 * (ctx->num_cmds - 1));
	close_parent_heredoc_fds(cmds);
	while (i < ctx->num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == ctx->num_cmds - 1)
			update_status_from_wait(status, data);
		i++;
	}
	free(ctx->pipefds);
	free(pids);
	return (data->last_status);
}

int	execute_pipeline(t_cmd *cmds, t_data *data)
{
	pid_t		*pids;
	t_pipe_ctx	ctx;

	if (init_pipeline_ctx(cmds, data, &ctx, &pids) != 0)
		return (1);
	if (ctx.num_cmds <= 0)
		return (0);
	if (fork_pipeline(cmds, &ctx, pids, data) != 0)
	{
		if (ctx.pipefds)
			free(ctx.pipefds);
		if (pids)
			free(pids);
		return (1);
	}
	return (wait_and_cleanup(cmds, data, &ctx, pids));
}
