#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

int	check_input_quotes(char *input)
{
	if (are_unclosed_quotes(input))
	{
		ft_putendl_fd("minishell: syntax error: unclosed quotes", 2);
		free(input);
		return (1);
	}
	return (0);
}

void	restore_stdio(int saved_in, int saved_out)
{
	if (saved_in >= 0)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out >= 0)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

int	is_builtin_name(char *name)
{
	if (!name)
		return (0);
	return (ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "env") == 0);
}

t_cmd	*get_cmds_from_input(char *input, t_data *data)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize_to_list(input);
	if (!tokens)
		return (NULL);
	clean_tokens(tokens, data);
	cmds = parse_tokens_to_cmds(tokens, data);
	free_tokens(tokens);
	return (cmds);
}
