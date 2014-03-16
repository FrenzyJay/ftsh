/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 01:12:39 by garm              #+#    #+#             */
/*   Updated: 2014/03/16 01:21:39 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum	e_tok
{
	TOK_UNCOMPLETED,
	TOK_CMD,
	TOK_ARG,
	TOK_SEPARATOR,
	TOK_HEREDOC,
	TOK_READ,
	TOK_WRITE,
	TOK_APPEND,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_SUBSH,
	TOK_BQUOTE,
	TOK_END
}				t_tok;

typedef struct	s_node
{
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
	t_tok			token;
	char			*value;
}				t_node;

#endif /* !PARSER_H */

