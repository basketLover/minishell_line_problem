#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static char	*try_path(const char *dir, const char *cmd)
{
	char	*full;

	full = ft_strjoin3(dir, "/", cmd);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*get_path_value(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_in_path(char *cmd, t_data *data)
{
	char	**paths;
	char	*path_value;
	char	*result;
	int		i;

	if (!cmd || !data)
		return (NULL);
	path_value = get_path_value(data->env);
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	result = NULL;
	while (paths[i] && !result)
		result = try_path(paths[i++], cmd);
	free_string_array(paths);
	return (result);
}

static void	main_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		input = readline("\033[38;5;201mminishell$ \033[0m");
		if (!input)
			break ;
		if (g_sig == SIGINT)
		{
			data->last_status = 130;
			g_sig = 0;
		}
		if (*input)
			add_history((input));
		process_input(input, data);
		if (g_sig)
		{
			data->last_status = 128 + g_sig;
			g_sig = 0;
		}
	}
	free(input);
	input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		env_count;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	setup_signals();
	env_count = count_env_vars(envp);
	data.env = copy_env(envp, env_count);
	data.last_status = 0;
	if (!data.env)
	{
		perror("env allocation failed");
		return (1);
	}
	main_loop((&data));
	ft_printf("exit\n");
	free_string_array(data.env);
	return (0);
}
