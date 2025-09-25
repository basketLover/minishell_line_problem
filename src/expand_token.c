#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static char	*process_dollar(char *result, char *token, int *i, t_data *data)
{
	char	*expanded;
	char	*temp;

	expanded = expand_variable(token, i, data);
	if (!expanded)
	{
		free(result);
		return (NULL);
	}
	temp = append_str(result, expanded);
	free(expanded);
	return (temp);
}

static char	*quote_state(char *result, char c, t_state *state)
{
	t_state	new;

	new = update_state(*state, c);
	if (new == *state)
		result = append_char(result, c);
	*state = new;
	return (result);
}

static char	*handle_dollar(char *result, char *token, int *i,
		t_data *data)
{
	result = process_dollar(result, token, i, data);
	(*i)--;
	return (result);
}

char	*expand_token(char *token, t_data *data)
{
	char	*result;
	int		i;
	t_state	state;

	if (!token)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	state = NORMAL;
	while (token[i])
	{
		if (token[i] && (token[i] == '\'' || token[i] == '"'))
			result = quote_state(result, token[i], &state);
		else if (token[i] == '$' && state != IN_SINGLE)
			result = handle_dollar(result, token, &i, data);
		else
			result = append_char(result, token[i]);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
