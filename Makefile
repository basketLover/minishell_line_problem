NAME        = minishell

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g $(INCLUDES)
LIBS        = -lreadline -lncurses -L$(LIBFT_DIR) -lft
INCLUDES    = -Ilibft -I.
RM 			= rm -rf
SRC_DIR 	= src/
OBJ_DIR 	= objects/
LIBFT_DIR   = libft/
LIBFT       = $(LIBFT_DIR)/libft.a

SRC         = minishell.c cd_builtin.c echo_builtin.c env_builtin.c \
				pwd_builtin.c export_builtin.c unset_builtin.c free.c \
				exit_builtin.c cd_utils.c utils.c heredoc.c error.c \
				signals.c expand.c parser.c env_utils.c redirections.c \
				export_utils.c expand_utils.c commands.c execute.c \
				tokenizer.c commands_utils.c process_input.c process_utils.c \
				pipe.c pipe_utils.c redirections_utils.c parse_tk_to_cmds.c \
				expand_token.c
				

OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))


all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re