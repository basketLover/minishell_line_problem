#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

t_state	update_state(t_state state, char ch)
{
	if (ch == '\'')
	{
		if (state == NORMAL)
			state = (IN_SINGLE);
		else if (state == IN_SINGLE)
			state = (NORMAL);
		else if (state == IN_DOUBLE)
			state = (IN_DOUBLE);
	}
	else if (ch == '"')
	{
		if (state == NORMAL)
			state = (IN_DOUBLE);
		else if (state == IN_DOUBLE)
			state = (NORMAL);
		else if (state == IN_SINGLE)
			state = (IN_SINGLE);
	}
	return (state);
}

static char	*handle_special_dollar(const char *str, int *i, t_data *data)
{
	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(data->last_status));
	}
	if (!ft_isalnum((unsigned char)str[*i + 1]) && str[*i + 1] != '_')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	return (NULL);
}

static char	*get_variable_value(const char *str, int *i, t_data *data,
	int start)
{
	char	*name;
	char	*value;
	char	*result;

	name = ft_substr(str, *i + 1, start - (*i + 1));
	if (!name)
		return (NULL);
	value = get_env_value(data->env, name);
	free(name);
	*i = start;
	if (value)
		result = ft_strdup(value);
	else
		result = ft_strdup("");
	return (result);
}

char	*expand_variable(const char *str, int *i, t_data *data)
{
	char	*res;
	int		start;

	if (!str || !i)
		return (NULL);
	if (!str[*i + 1])
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	res = handle_special_dollar(str, i, data);
	if (res)
		return (res);
	start = *i + 1;
	while (str[start] && (ft_isalnum((unsigned char)str[start])
			|| str[start] == '_'))
		start++;
	return (get_variable_value(str, i, data, start));
}
