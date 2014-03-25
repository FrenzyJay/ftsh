#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 18:33:50 by jvincent          #+#    #+#              #
#    Updated: 2014/03/25 18:13:16 by jibanez          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = 			cc
NAME = 			ftsh
CFLAGS = 		-Wall -Werror -Wextra -g
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
				srcs/term_mode.c
OBJ = 			$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
	@make -sC libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
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
