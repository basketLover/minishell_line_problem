#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = temp;
	}
}

void	free_redirs(t_redir *r)
{
	t_redir	*temp;

	while (r)
	{
		temp = r->next;
		if (r->target)
			free(r->target);
		free(r);
		r = temp;
	}
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*temp;

	while (head)
	{
		temp = head->next;
		if (head->argv)
			free_string_array(head->argv);
		free_redirs(head->redirs);
		free(head);
		head = temp;
	}
}

void	free_cmds_and_input(t_cmd *cmds, char *input)
{
	free_cmds(cmds);
	free(input);
}
