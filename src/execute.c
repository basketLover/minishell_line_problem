#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static char	*get_command_path(t_cmd *cmds, t_data *data)
{
	char	*full_path;

	if (ft_strchr(cmds->argv[0], '/'))
		full_path = cmds->argv[0];
	else
		full_path = find_in_path(cmds->argv[0], data);
	return (full_path);
}

static void	check_path_status(char *full_path)
{
	struct stat	st;

	if (stat(full_path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putendl_fd(ft_strjoin3("minishell: ", full_path,
					": Is a directory"), 2);
			exit(126);
		}
		if (access(full_path, X_OK) != 0)
		{
			ft_putendl_fd(ft_strjoin3("minishell: ", full_path,
					": Permission denied"), 2);
			exit(126);
		}
	}
}

void	exec_child_command(t_cmd *cmds, t_data *data)
{
	char				*full_path;

	if (!cmds->argv[0] || cmds->argv[0][0] == '\0')
		exit (0);
	setup_child_signals();
	if (cmds->redirs && apply_redirections_child(cmds, data) != 0)
		exit (1);
	full_path = get_command_path(cmds, data);
	if (!full_path)
		handle_invalid_path(cmds->argv[0]);
	check_path_status(full_path);
	execve(full_path, cmds->argv, data->env);
	if (ft_strchr(cmds->argv[0], '/'))
	{
		perror(cmds->argv[0]);
		exit (127);
	}
	else
		handle_invalid_path(full_path);
}

int	execute_cmds(t_cmd *cmds, t_data *data)
{
	pid_t	pid;

	if (!cmds || !cmds->argv ||!cmds->argv[0])
		return (-1);
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
		exec_child_command(cmds, data);
	execute_program(pid, data);
	return (data->last_status);
}

void	execute_program(pid_t pid, t_data *data)
{
	int	sig;
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->last_status = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		data->last_status = 128 + sig;
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		else if (sig == SIGINT)
			write(1, "\n", 1);
	}
	else
		data->last_status = 1;
}
