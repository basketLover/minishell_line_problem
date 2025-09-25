#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

void	bubble_sort_env(char **env, int count)
{
	int		i;
	int		sorted;
	char	*tmp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

char	**sort_env_copy(char **env)
{
	int		count;
	char	**copy;

	count = count_env_vars(env);
	copy = copy_env(env, count);
	if (!copy)
		return (NULL);
	bubble_sort_env(copy, count);
	return (copy);
}
