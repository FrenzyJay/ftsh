#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 18:33:50 by jvincent          #+#    #+#              #
#    Updated: 2014/03/27 05:26:20 by jvincent         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC =			gcc
NAME =			ftsh

ifeq ($(DEBUG), 1)
	FLAGS =	 -Wall -Wextra -pedantic
	CC = cc -g
else
	FLAGS =	-Wall -Werror -Wextra -pedantic
endif

CFLAGS +=		-I./includes \
				-I./libft/includes \
				-I./libft/printf/includes

LDFLAGS = 		-L libft -lft \
				-L /usr/lib -ltermcap

INCLUDE_LIB = 	libft/includes
LIB = 			libft

SRCS = 			srcs/main.c \
				srcs/ft_exec.c \
				srcs/ft_env.c \
				srcs/ft_builtin.c \
				srcs/ft_init.c \
				srcs/dyn_buff.c \
				srcs/key_arrows.c \
				srcs/key_del.c \
				srcs/key_hook.c \
				srcs/key_travel.c \
				srcs/prompt.c \
				srcs/puts.c \
				srcs/read_line.c \
				srcs/refresh.c \
				srcs/t_hlst.c \
				srcs/term_mode.c \
				srcs/debug.c \
				srcs/lexer.c \
				srcs/tokens.c \
				srcs/tokens_utils.c \
				srcs/ast.c \
				srcs/parser_error.c \
				srcs/parser.c \
				srcs/parser_core.c \
				srcs/ft_destroy_errting.c \
				srcs/ft_process_lst.c \
				srcs/ft_jobs_action.c \
				srcs/ft_signals.c \
				srcs/ft_jobs_lst.c \
				srcs/ft_jobs_functions.c

OBJ =			$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(FLAGS)

$(NAME): $(OBJ)
	@make -sC libft
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
	@echo $(NAME) ok

clean:
	@make clean -sC libft
	@rm -f $(OBJ)
	@echo Objects deleted : $(NAME)

fclean: clean
	@make fclean -sC libft
	@rm -f $(NAME)
	@echo $(NAME) deleted

re: fclean all

.PHONY: clean fclean re all

