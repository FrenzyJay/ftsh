#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 18:33:50 by jvincent          #+#    #+#              #
##   Updated: 2014/03/21 13:50:02 by garm             ###   ########.fr       ##
#                                                                              #
#******************************************************************************#

CC =			gcc
NAME =			42sh

ifeq ($(DEBUG), 1)
	FLAGS =	-g -Wall -Wextra -pedantic
	CC = cc
else
	FLAGS =	-Wall -Werror -Wextra -pedantic
endif

CFLAGS +=		-I./includes \
				-I./libft/includes \
				-I./libft/printf/includes

LDFLAGS =		-L libft -lft

INCLUDE_LIB =	libft/includes
LIB =			libft

SRCS =			srcs/main.c \
				srcs/debug.c \
				srcs/exec.c \
				srcs/lexer.c \
				srcs/tokens.c \
				srcs/tokens_utils.c \
				srcs/ast.c \
				srcs/parser.c \
				srcs/parser_core.c

OBJ =			$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(FLAGS)

$(NAME): $(OBJ)
	@make -sC libft
	@$(CC) $(CFLAGS) $(FLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
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

