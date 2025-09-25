#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 
#include "minishell.h" 
#include "libft/libft.h" 

int	swap_stdin_with_fd(int fd)
{
	int	saved_in;

	saved_in = dup(STDIN_FILENO);
	if (saved_in < 0)
	{
		perror("dup");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(saved_in);
		return (-1);
	}
	close(fd);
	return (saved_in);
}

void	restore_stdin(int saved_in)
{
	if (saved_in >= 0)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
}

static int	write_heredoc_line(int fd, char *line, int quoted,
		t_data *data)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_token(line, data);
		if (!expanded)
			return (free(line), 1);
		ft_putendl_fd(expanded, fd);
		free(expanded);
	}
	else
		ft_putendl_fd(line, fd);
	free(line);
	return (0);
}

int	write_heredoc_input(int fd, char *delim, int delim_quoted,
		t_data *data)
{
	char	*line;

	if (!delim)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putendl_fd(ft_strjoin3("minishell: warning: \
					here-document delimited by end-of-file \
					(wanted '", delim, "')"), 2);
			break ;
		}
		if (g_sig || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (write_heredoc_line(fd, line, delim_quoted, data) != 0)
			return (1);
	}
	rl_clear_history();
	return (g_sig);
}

int	handle_heredoc(char *delim, int delim_quoted, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;

	if (!delim)
		return (-1);
	if (pipe(pipefd) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		write_heredoc_input(pipefd[1], delim, delim_quoted, data);
		close(pipefd[1]);
		_exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	return (pipefd[0]);
}
