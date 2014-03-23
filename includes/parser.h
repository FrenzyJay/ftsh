/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 01:12:39 by garm              #+#    #+#             */
/*   Updated: 2014/03/23 00:46:35 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NB_TOKVALS 12
# define NB_TOKENS 16
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
int		ft_getsize_separator(char *entry);
int		ft_is_uncompleted(char *value);
t_lex	*ft_lexer_end(t_lex *lex);

/*
** debug.c
*/
char	*ft_toktostr(t_tok token);
void	ft_putlex(t_lex *lex);

/*
** parser.c
*/
t_node	*ft_parser(char *entry);
t_lex	*ft_parser_find(t_lex *head, t_lex *tail, t_tok tok);
t_lex	*ft_parser_find2(t_lex *head, t_lex *tail, t_tok tok1, t_tok tok2);

/*
** parser_core.c
*/
t_node	*ft_parse_end(t_lex *head, t_node *tree);
t_node	*ft_parse_logic(t_lex *head, t_lex *tail, t_node *tree);
t_node	*ft_parse_pipeline(t_lex *head, t_lex *tail, t_node *tree, int ktr);
t_node	*ft_parse_redirections(t_lex *head, t_lex *tail, t_node *tree, int s);
/*t_node	*ft_parse_cmd(t_lex *head, t_lex *tail, t_node *tree);*/

/*
** ast.c
*/
t_node	*ft_ast_add(t_node *tree, t_lex *elem, char side);

#endif /* !PARSER_H */

