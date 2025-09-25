#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

int	handle_builtin(char **args, t_data *data)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (data->last_status = echo_builtin(args, data));
	if (ft_strcmp(args[0], "cd") == 0)
		return (data->last_status = cd_builtin(args, data));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (data->last_status = pwd_builtin(args, data));
	if (ft_strcmp(args[0], "export") == 0)
		return (data->last_status = export_builtin(args, data));
	if (ft_strcmp(args[0], "unset") == 0)
		return (data->last_status = unset_builtin(args, data));
	if (ft_strcmp(args[0], "env") == 0)
		return (data->last_status = env_builtin(args, data));
	return (-1);
}

int	manage_builtin(t_cmd *cmds, t_data *data, char *input)
{
	int	ret;
	int	saved_in;
	int	saved_out;

	(void)input;
	if (!cmds || !cmds->argv || !cmds->argv[0])
		return (0);
	if (ft_strcmp(cmds->argv[0], "exit") == 0)
	{
		ret = exit_builtin(cmds->argv, data, input);
		if (ret == 2)
			return (1);
		return (ret);
	}
	if (!is_builtin_name(cmds->argv[0]))
		return (0);
	if (cmds->redirs && apply_redirections(cmds, &saved_in,
			&saved_out, data) != 0)
		return (data->last_status = 1, 1);
	data->last_status = handle_builtin(cmds->argv, data);
	if (cmds->redirs)
		restore_stdio(saved_in, saved_out);
	return (1);
}

static int	handle_single_cmd(t_cmd *cmd, t_data *data, char *input)
{
	if (cmd->argv && cmd->argv[0])
	{
		if (manage_builtin(cmd, data, input))
			return (1);
	}
	return (0);
}

static int	execute_cmds_wrapper(t_cmd *cmds, t_data *data)
{
	if (cmds->next)
		return (execute_pipeline(cmds, data));
	return (execute_cmds(cmds, data));
}

void	process_input(char *input, t_data *data)
{
	t_cmd	*cmds;
	int		status;

	if (!input || check_input_quotes(input))
		return ;
	cmds = get_cmds_from_input(input, data);
	if (!cmds)
		return (free(input));
	trim_argv(cmds);
	if (!cmds->argv[0])
		return (free_cmds_and_input(cmds, input));
	if (prepare_heredocs_for_cmds(cmds, data) != 0)
		return (free_cmds_and_input(cmds, input));
	if (!cmds->next && handle_single_cmd(cmds, data, input))
		return (free_cmds_and_input(cmds, input));
	status = execute_cmds_wrapper(cmds, data);
	if (status >= 0)
		data->last_status = status;
	free_cmds_and_input(cmds, input);
}
