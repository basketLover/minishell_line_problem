# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 12:23:09 by mariserr          #+#    #+#              #
#    Updated: 2025/05/12 14:54:01 by mdolores         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		libft.a

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror -g -MMD

AR			=		ar
ARFLAGS		=		rcs

RM			=		rm -rf
SRC_DIR		=		sources
PRINTF_DIR	=		ft_printf
OBJ_DIR		=		obj
OBJPF_DIR	=		objpf

SRCS		= 		ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset ft_bzero \
					ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr ft_strrchr \
					ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strdup ft_substr \
					ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri ft_putchar_fd \
					ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_lstnew_bonus ft_lstadd_front_bonus \
					ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
					ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus 

SRC			=		$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(SRCS)))

SRCSPF		=		ft_printf ft_get_type \

SRCPF		=		$(addsuffix .c, $(addprefix $(PRINTF_DIR)/, $(SRCSPF)))

OBJ			=		$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJPF		=		$(SRCPF:$(PRINTF_DIR)/%.c=$(OBJPF_DIR)/%.o)

DEPS		=		$(OBJ:.o=.d) $(OBJPF:.o=.d)

PRINTF_PATH	=		ft_printf/

PRINTF		=		$(PRINTF_PATH)/libftprintf.a

OBJPF_DIR	=		objpf

OBJPF		=		$(SRCPF:ft_printf/%.c=$(OBJPF_DIR)/%.o)

$(OBJ_DIR)/%.o:		sources/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJPF_DIR)/%.o:	ft_printf/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ_DIR) $(OBJ) $(OBJPF_DIR) $(OBJPF)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ) $(OBJPF)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJPF_DIR):
	mkdir -p $(OBJPF_DIR)


all: 	$(NAME)

clean:
	$(RM) $(OBJ_DIR) $(OBJPF_DIR)

fclean: clean
	$(RM) $(NAME)

re: 	fclean all
-include $(DEPS)

.PHONY:	all clean fclean re
