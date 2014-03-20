/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 01:12:39 by garm              #+#    #+#             */
/*   Updated: 2014/03/20 01:17:26 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NB_TOKVALS 12
# define NB_TOKENS 15
# define FT_ISQUOTE(C) (C == '\'' || C == '"' || C == '`')

# define TOK_IS_LEFT_RE(T) (T == TOK_READ || T == TOK_HEREDOC)
# define TOK_IS_RIGHT_RE(T) (T == TOK_WRITE || T == TOK_APPEND)
# define FT_TOK_IS_REDIRECTION(T) (TOK_IS_LEFT_RE(T) || TOK_IS_RIGHT_RE(T))

typedef enum	e_tok
{
	TOK_SEPARATOR,
	TOK_UNCOMPLETED,
	TOK_EXPR,
	TOK_HEREDOC,
	TOK_READ,
	TOK_WRITE,
	TOK_APPEND,
	TOK_CMD,
	TOK_ARG,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_SUBSH,
	TOK_END,
	TOK_BG
}				t_tok;

typedef struct s_tokval
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

/*
** lexer.c
*/
char	*ft_strsuck(char **str, unsigned long len);
t_lex	*ft_lex_push(t_lex *lex, t_tok token, char *value);
void	ft_lex_destroy(t_lex **lex);
t_lex	*ft_lexer(char *entry, t_lex *lextable);

/*
** tokens.c
*/
int		ft_is_tok(char *entry);
t_tok	ft_get_tok(char *tval);
void	ft_get_tokvals(t_tokval *tokvals);

/*
** tokens_utils.c
*/
char	*gettok(t_tok token);
void	ft_putlex(t_lex *lex);
int		ft_getsize_separator(char *entry);
int		ft_is_uncompleted(char *value);

#endif /* !PARSER_H */

