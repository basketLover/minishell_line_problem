#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static int	replace_env_var(char ***env, const char *key,
	char *new_var, size_t key_len)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0
			&& (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_env_var(char ***env, char *new_var, int count)
{
	char	**new_env;

	new_env = realloc_env(*env, count + 2);
	if (!new_env)
	{
		free(new_var);
		return (1);
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	*env = new_env;
	return (0);
}

int	set_env_var(char ***env, const char *key, const char *value)
{
	char	*new_var;
	int		i;
	size_t	key_len;

	if (!key || !value || !*env)
		return (1);
	key_len = ft_strlen(key);
	new_var = ft_strjoin3(key, "=", value);
	if (!new_var)
		return (1);
	if (replace_env_var(env, key, new_var, key_len))
		return (0);
	i = 0;
	while ((*env)[i])
		i++;
	return (add_env_var(env, new_var, i));
}
