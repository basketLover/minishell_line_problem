#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

int	env_builtin(char **args, t_data *data)
{
	int	i;

	i = 0;
	(void)args;
	if (args[1] && ft_strcmp(args[1], "-i") == 0)
		return (0);
	else
	{
		while (data->env[i])
		{
			ft_printf("%s\n", data->env[i]);
			i++;
		}
	}
	return (0);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	size_t	total_len;
	char	*joined;

	len1 = strlen(s1);
	len2 = strlen(s2);
	len3 = strlen(s3);
	total_len = len1 + len2 + len3 + 1;
	joined = malloc(total_len);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, total_len);
	ft_strlcat(joined, s2, total_len);
	ft_strlcat(joined, s3, total_len);
	return (joined);
}

char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = strlen(key);
	while (env[i] != NULL)
	{
		if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char	**realloc_env(char **env, int new_size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * new_size);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i] && i < new_size - 1)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	if (env)
		free(env);
	return (new_env);
}
