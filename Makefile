#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 18:33:50 by jvincent          #+#    #+#              #
#    Updated: 2014/02/16 17:29:09 by jvincent         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = 			cc
NAME = 			42sh
CFLAGS = 		-Wall -Werror -Wextra -g
CFLAGS +=		-I./includes \
				-I./libft/includes \
				-I./libft/printf/includes
LDFLAGS = 		-L libft -lft
INCLUDE_LIB = 	libft/includes
LIB = 			libft
SRCS = 			srcs/main.c \
				srcs/exec.c
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
