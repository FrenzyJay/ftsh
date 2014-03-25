/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 01:12:39 by garm              #+#    #+#             */
/*   Updated: 2014/03/25 19:57:47 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NB_TOKVALS 12
# define NB_TOKENS 15
# define FT_ISQUOTE(C) (C == '\'' || C == '"' || C == '`')

# define TOK_IS_LEFT_RE(T) ((T) == tok_read || (T) == tok_heredoc)
# define TOK_IS_RIGHT_RE(T) ((T) == tok_write || (T) == tok_append)
# define TOK_IS_REDIRECTION(T) (TOK_IS_LEFT_RE(T) || TOK_IS_RIGHT_RE(T))

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
void	ft_put_ast(t_node *tree, int side);
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
t_node	*ft_parse_cmd(t_lex *head, t_lex *tail, t_node *tree, int side);

/*
** ast.c
*/
t_node	*ft_ast_add(t_node *tree, t_lex *elem, char side);
t_node	*ft_ast_rewind(t_node *tree);

/*
** parser_error.c
*/
char	*ft_parser_check_error(t_node **ast);

#endif /* !PARSER_H */
