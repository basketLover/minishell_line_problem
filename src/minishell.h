#ifndef MINISHELL_H
# define MINISHELL_H

# define INITIAL_SIZE 256 

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft/ft_printf/ft_printf.h"

extern int	g_sig;

typedef struct s_data
{
	char	**env;
	int		last_status;
}	t_data;

typedef enum e_state
{
	NORMAL,
	IN_SINGLE,
	IN_DOUBLE,
}	t_state;

typedef enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND
}	t_toktype;

typedef struct s_token
{
	char			*value;
	int				quoted;
	t_toktype		type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_toktype		type;
	char			*target;
	int				fd;
	int				quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipe_ctx
{
	int		*pipefds;
	int		num_cmds;
	t_data	*data;
}	t_pipe_ctx;

typedef struct s_cmd
{
	char			**argv;
	int				argc;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

void	handle_sigint(int sig);
void	setup_signals(void);
void	setup_child_signals(void);

void	process_input(char *input, t_data *data);
void	trim_argv(t_cmd *cmds);
int		is_builtin_name(char *name);
t_cmd	*get_cmds_from_input(char *input, t_data *data);
int		check_input_quotes(char *input);
void	clean_tokens(t_token *head, t_data *data);
void	restore_stdio(int saved_in, int saved_out);

int		handle_builtin(char **args, t_data *data);
int		echo_builtin(char **args, t_data *data);
int		cd_builtin(char **args, t_data *data);
int		pwd_builtin(char **args, t_data *data);
int		export_builtin(char **args, t_data *data);
int		unset_builtin(char **args, t_data *data);
int		env_builtin(char **args, t_data *data);
int		exit_builtin(char **args, t_data *data, char *input);

int		handle_chdir_error(char *oldpwd);
char	*safe_getcwd(void);
void	update_pwd_and_oldpwd(char *oldpwd, char *pwd, char ***env);
int		cd_to_home(t_data *data);
int		cd_to_path(char *path, t_data *data);
char	*find_in_path(char *cmd, t_data *data);
void	handle_invalid_path(char *cmd);

char	*expand_variable(const char *str, int *i, t_data *data);
char	*append_char(char *result, char ch);
char	*append_str(char *result, const char *s);
char	*expand_token(char *token, t_data *data);
void	append_token(t_token **head, char *value, t_toktype type, int quoted);
t_state	update_state(t_state state, char ch);

int		count_cmds(t_cmd *cmds);
int		execute_cmds(t_cmd *cmds, t_data *data);
int		execute_pipeline(t_cmd *cmds, t_data *data);
void	execute_program(pid_t pid, t_data *data);
int		prepare_heredocs_for_cmds(t_cmd *cmds, t_data *data);
void	close_parent_heredoc_fds(t_cmd *cmds);
void	exec_child_command(t_cmd *cmds, t_data *data);
void	append_cmd(t_cmd **head, t_cmd *new_cmd);
t_token	*tokenize_to_list(char *input);
t_cmd	*create_cmd(char **argv, int argc, t_redir *redirs);
t_cmd	*parse_tokens_to_cmds(t_token *tokens, t_data *data);
void	setup_child_pipes(int *pipefds, int i, int num_cmds);
void	close_all_pipes(int *pipefds, int n);
int		create_pipes_for_ctx(t_pipe_ctx *ctx);
void	update_status_from_wait(int status, t_data *data);

int		set_env_var(char ***env, const char *key, const char *value);
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char	**realloc_env(char **env, int new_size);
char	*get_env_value(char **env, const char *key);
char	**copy_env(char **env, int count);
char	**sort_env_copy(char **env);
void	bubble_sort_env(char **env, int count);

int		count_env_vars(char **env);
int		ft_strcmp(char *s1, char *s2);
int		is_valid_identifier(char *s);
int		are_unclosed_quotes(char *str);

int		ft_is_space(char c);
char	**ft_realloc_argv(char **argv, int argc, char *new_str);

int		handle_heredoc(char *delim, int delim_quoted, t_data *data);
int		handle_redirections(t_cmd *cmd, t_data *data);
t_redir	*create_redir(t_toktype type, char *target, int quoted);
void	append_redir(t_redir **head, t_redir *new_redir);
int		apply_redirections(t_cmd *cmd, int *saved_in, int *saved_out,
			t_data *data);
int		apply_redirections_child(t_cmd *cmd, t_data *data);
int		write_heredoc_input(int fd, char *delim, int delim_quoted,
			t_data *data);
int		swap_stdin_with_fd(int fd);

void	print_declare_line(char *entry);
void	rl_print_error_and_reset_prompt(char *msg);
void	free_cmds_and_input(t_cmd *cmds, char *input);
void	free_string_array(char **array);
void	free_tokens(t_token *head);
void	free_redirs(t_redir *r);
void	free_cmds(t_cmd *head);

#endif
