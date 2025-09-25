# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 09:44:08 by mariserr          #+#    #+#              #
#    Updated: 2025/05/12 11:40:47 by mdolores         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -MMD

RM			= rm -fr

SRCS		= ft_printf.c ft_get_type.c
SRC			= $(addsuffix .c, $(addprefix sources/, $(SRCS)))

OBJ_DIR		= obj
OBJ			= $(SRC:sources/%.c=$(OBJ_DIR)/%.o)
DEPS		=	$(OBJ:.o=.d)

LIBFT_PATH	=	../sources
LIBFT		=	$(LIBFT_PATH)/libft.a

all:					$(LIBFT)

$(OBJ_DIR)/%.o:	sources/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):		$(OBJ_DIR) $(OBJ)
	$(MAKE) -C $(LIBFT_PATH) all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJ_DIR)

fclean:			clean
	$(MAKE) -C $(LIBFT_PATH) fclean

re:				fclean all
-include $(DEPS)

.PHONY:	all clean fclean re libft
