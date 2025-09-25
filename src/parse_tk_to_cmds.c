#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static int	handle_redir_token(t_token **token, t_redir **redirs, t_data *data)
{
	t_toktype	type;

	type = (*token)->type;
	*token = (*token)->next;
	if (*token && (*token)->type == T_WORD)
	{
		append_redir(redirs, create_redir(type, (*token)->value,
				(*token)->quoted));
		return (0);
	}
	ft_putendl_fd("minishell: syntax error near redirection", 2);
	if (data)
		data->last_status = 2;
	return (1);
}

static void	handle_pipe_token(t_cmd **head_cmd, t_cmd *cmd)
{
	append_cmd(head_cmd, create_cmd(cmd->argv, cmd->argc, cmd->redirs));
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
}

static void	handle_word_token(t_token *token, t_cmd *cmd)
{
	cmd->argv = ft_realloc_argv(cmd->argv, cmd->argc, token->value);
	cmd->argc++;
}

static int	process_token(t_token **token, t_cmd **head_cmd, t_cmd *current_cmd,
		t_data *data)
{
	if ((*token)->type == T_WORD)
		handle_word_token(*token, current_cmd);
	else if ((*token)->type == T_REDIR_IN || (*token)->type == T_REDIR_OUT
		|| (*token)->type == T_HEREDOC || (*token)->type == T_APPEND)
	{
		if (handle_redir_token(token, &current_cmd->redirs, data) != 0)
			return (1);
	}
	else if ((*token)->type == T_PIPE)
		handle_pipe_token(head_cmd, current_cmd);
	return (0);
}

t_cmd	*parse_tokens_to_cmds(t_token *token_head, t_data *data)
{
	t_cmd	*head_cmd;
	t_cmd	current_cmd;
	t_token	*token;

	head_cmd = NULL;
	current_cmd.argv = NULL;
	current_cmd.argc = 0;
	current_cmd.redirs = NULL;
	token = token_head;
	while (token)
	{
		if (process_token(&token, &head_cmd, &current_cmd, data) != 0)
			return (NULL);
		token = token->next;
	}
	if (current_cmd.argc > 0 || current_cmd.redirs)
		append_cmd(&head_cmd, create_cmd(current_cmd.argv,
				current_cmd.argc, current_cmd.redirs));
	return (head_cmd);
}
