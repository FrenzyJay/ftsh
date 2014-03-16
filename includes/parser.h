/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 01:12:39 by garm              #+#    #+#             */
/*   Updated: 2014/03/16 13:40:47 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NB_TOKVALS 11
# define FT_ISQUOTE(C) (C == '\'' || C == '"' || C == '`')

typedef enum	e_tok
{
	TOK_UNCOMPLETED,
	TOK_EXPR,
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

typedef struct s_tokval
{
	t_tok	token;
	char	*value;
}				t_tokval;

typedef struct	s_lex
{
	struct s_lex	*left;
	struct s_lex	*right;
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

/*
** lexer.c
*/
t_lex	*ft_lexer(char *entry, t_lex *lextable, t_lex *prev_tok);

/*
** tokens.c
*/
int		ft_is_tok(char *entry);
t_tok	ft_get_token(char *tval);

/*
** tokens_utils.c
*/
int		ft_getsize_separator(char *entry);
int		ft_is_uncompleted(char *value);

#endif /* !PARSER_H */

