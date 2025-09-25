#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

char	*append_char(char *result, char ch)
{
	char	c[2];
	char	*temp;

	c[0] = ch;
	c[1] = '\0';
	temp = ft_strjoin(result, c);
	free(result);
	return (temp);
}

char	*append_str(char *result, const char *s)
{
	char	*temp;

	temp = ft_strjoin(result, s);
	free(result);
	return (temp);
}

void	clean_tokens(t_token *head, t_data *data)
{
	t_token	*cur;
	char	*expanded;

	cur = head;
	while (cur)
	{
		expanded = expand_token(cur->value, data);
		free(cur->value);
		cur->value = expanded;
		cur = cur->next;
	}
}
