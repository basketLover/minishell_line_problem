#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

char	**copy_env(char **env, int count)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[i--]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	print_declare_line(char *entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		ft_printf("declare -x %s=\"%s\"\n", entry, equal_sign + 1);
		*equal_sign = '=';
	}
	else
		ft_printf("declare -x %s\n", entry);
}

int	print_export(t_data *data)
{
	char	**sorted;
	int		i;

	sorted = sort_env_copy(data->env);
	if (!sorted)
		return (1);
	i = 0;
	while (sorted[i])
	{
		print_declare_line(sorted[i]);
		free(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

int	process_export_arg(char *arg, t_data *data)
{
	char	*equal;
	char	*key;
	char	*value;
	int		key_len;

	if (!is_valid_identifier(arg))
		return (0);
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key_len = equal - arg;
		key = ft_substr(arg, 0, key_len);
		value = ft_strdup(equal + 1);
		if (!key || !value)
			return (0);
		if (value[0] != '\0')
			set_env_var(&data->env, key, value);
		free(key);
		free(value);
	}
	return (1);
}

int	export_builtin(char **args, t_data *data)
{
	int	i;
	int	status;

	if (!args[1])
		return (print_export(data), 0);
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!process_export_arg(args[i], data))
		{
			ft_putendl_fd(ft_strjoin3("export: '", args[i],
					"': not a valid identifier"), 2);
			status = 1;
		}
		i++;
	}
	return (status);
}
