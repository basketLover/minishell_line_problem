#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

int	count_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = cmds;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

void	setup_child_pipes(int *pipefds, int i, int num_cmds)
{
	if (i > 0 && dup2(pipefds[(i - 1) * 2], STDIN_FILENO) < 0)
		perror("dup2");
	if (i < num_cmds - 1 && dup2(pipefds[i * 2 + 1], STDOUT_FILENO) < 0)
		perror(("dup2"));
}

void	close_all_pipes(int *pipefds, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipefds[i]);
		i++;
	}
}

void	update_status_from_wait(int status, t_data *data)
{
	if (WIFEXITED(status))
		data->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_status = 128 + WTERMSIG(status);
}

int	create_pipes_for_ctx(t_pipe_ctx *ctx)
{
	int	i;
	int	pipe_count;

	i = 0;
	if (!ctx)
		return (-1);
	pipe_count = ctx->num_cmds - 1;
	while (i < pipe_count)
	{
		if (pipe(&ctx->pipefds[i * 2]) < 0)
		{
			perror("pipe");
			return (-1);
		}
		i = i + 1;
	}
	return (0);
}
