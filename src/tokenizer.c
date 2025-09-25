#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static int	handle_operator(char *input, int *i, t_token **head)
{
	if (input[*i] == '|')
		append_token(head, "|", T_PIPE, 0);
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		append_token(head, ">>", T_APPEND, 0);
		(*i)++;
	}
	else if (input[*i] == '>')
		append_token(head, ">", T_REDIR_OUT, 0);
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		append_token(head, "<<", T_HEREDOC, 0);
		(*i)++;
	}
	else if (input[*i] == '<')
		append_token(head, "<", T_REDIR_IN, 0);
	else
		return (0);
	(*i)++;
	return (1);
}

static int	handle_quote(char *input, int *i)
{
	char	quote;

	if (!input || !i)
		return (1);
	quote = input[*i];
	(*i)++;
	while (input[*i])
	{
		if (g_sig)
			return (1);
		if (input[*i] == quote)
		{
			(*i)++;
			return (0);
		}
		(*i)++;
	}
	rl_print_error_and_reset_prompt(
		"minishell: syntax error: unclosed quotes");
	return (1);
}

static void	handle_word(char *input, int *i, t_token **head)
{
	int		len;
	int		start;
	int		quoted;
	char	*token_str;

	start = *i;
	quoted = 0;
	while (input[*i] && !ft_is_space(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quoted = 1;
			if (handle_quote(input, i))
				return ;
		}
		else
			(*i)++;
	}
	len = *i - start;
	token_str = ft_substr(input, start, len);
	if (!token_str)
		return (free(token_str));
	append_token(head, token_str, T_WORD, quoted);
	free(token_str);
}

t_token	*tokenize_to_list(char *input)
{
	int		i;
	int		len;
	t_token	*head;

	i = 0;
	head = NULL;
	len = ft_strlen(input);
	while (i < len)
	{
		if (ft_is_space(input[i]))
		{
			i++;
			continue ;
		}
		if (handle_operator(input, &i, &head))
			continue ;
		handle_word(input, &i, &head);
	}
	return (head);
}
