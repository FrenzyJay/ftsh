/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:13:26 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 19:18:56 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>

typedef enum	e_tok
{
	tok_separator,
	tok_uncompleted,
	tok_expr,
	tok_heredoc,
	tok_read,
	tok_write,
	tok_append,
	tok_cmd,
	tok_arg,
	tok_pipe,
	tok_and,
	tok_or,
	tok_subsh,
	tok_end,
	tok_bg
}				t_tok;

typedef struct	s_tokval
{
	t_tok	token;
	char	*value;
}				t_tokval;

typedef struct	s_lex
{
	struct s_lex	*prev;
	struct s_lex	*next;
	t_tok			token;
	char			*value;
}				t_lex;

typedef struct	s_node
{
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
	t_tok			token;
	char			*value;
}				t_node;

typedef struct			s_process
{
	pid_t				pid;
	char				**argv;
	char				state;
	char				completed;
	char				stopped;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	int					num;
	char				recent;
	t_process			*first_process;
	pid_t				pgid;
	struct s_job		*next;
	struct s_job		*prev;
}						t_job;

#endif

