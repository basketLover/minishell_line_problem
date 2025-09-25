#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static void	update_single_q(char c, int *in_single, int in_double)
{
	if (c == '\'' && in_double == 0)
	{
		if (*in_single == 0)
			*in_single = 1;
		else
			*in_single = 0;
	}
}

static void	update_double_q(char c, int *in_double, int in_Single)
{
	if (c == '"' && in_Single == 0)
	{
		if (*in_double == 0)
			*in_double = 1;
		else
			*in_double = 0;
	}
}

int	are_unclosed_quotes(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	if (!str)
		return (0);
	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		update_single_q(str[i], &in_single, in_double);
		update_double_q(str[i], &in_double, in_single);
		i++;
	}
	if (in_single || in_double)
		return (1);
	return (0);
}
