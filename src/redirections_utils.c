#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

int	prepare_heredocs_for_cmds(t_cmd *cmds, t_data *data)
{
	t_cmd	*cur;
	t_redir	*r;

	cur = cmds;
	while (cur)
	{
		r = cur->redirs;
		while (r)
		{
			if (r->type == T_HEREDOC)
			{
				if (r->fd >= 0)
					close(r->fd);
				r->fd = handle_heredoc(r->target, r->quoted, data);
				if (r->fd < 0)
				{
					ft_putendl_fd("minishell: failed to create heredoc", 2);
					return (-1);
				}
			}
			r = r->next;
		}
		cur = cur->next;
	}
	return (0);
}
