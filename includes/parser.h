/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 01:12:39 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 19:19:00 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NB_TOKVALS 12
# define NB_TOKENS 15
# define FT_ISQUOTE(C) (C == '\'' || C == '"' || C == '`')

# define STATE_ERROR -3
# define STATE_ERROR_OUTPUT -2
# define STATE_ERROR_INPUT -1
# define STATE_NORW 0
# define STATE_READ 1
# define STATE_WRITE 2
# define STATE_RW 3

# define TOK_IS_LEFT_RE(T) ((T) == tok_read || (T) == tok_heredoc)
# define TOK_IS_RIGHT_RE(T) ((T) == tok_write || (T) == tok_append)
# define TOK_IS_RE(T) (TOK_IS_LEFT_RE(T) || TOK_IS_RIGHT_RE(T))
# define TOK_IS_LOGIC(T) ((T) == tok_and || (T) == tok_or)
# define TOK_IS_END(T) ((T) == tok_end || (T) == tok_bg)

# define CHECK_EXPR_PARENT(T) ((T) == tok_subsh)
# define CHECK_RE_PARENT(T) ((T) == tok_expr || (T) == tok_subsh)
# define CHECK_END_PARENT(T) ((T) == tok_pipe || TOK_IS_LOGIC(T))
# define CHECK_SUBSH_PARENT(T) ((T) == tok_subsh || (T) == tok_expr)

# define CHECK_LOGIC_PARENT_2(T) (TOK_IS_LOGIC(T) || TOK_IS_END(T))
# define CHECK_LOGIC_PARENT(T) ((T) == tok_pipe || CHECK_LOGIC_PARENT_2(T))

# define CHECK_PIPE_PARENT_2(T) ((T) == tok_subsh || (T) == tok_expr)
# define CHECK_PIPE_PARENT(T) (CHECK_PIPE_PARENT_2(T) || TOK_IS_RE(T))

# define CHECK_PIPE(T) ((T) == tok_expr || TOK_IS_RE(T))

# include "struct.h"

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
void	ft_put_ast(t_node *tree);
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
void	ft_ast_stack_right(t_node *tree, t_lex *elem);
t_node	*ft_ast_rewind(t_node *tree);
void	ft_ast_destroy(t_node **ast);

/*
** parser_error.c
*/
char	*ft_parser_check_error(t_node *ast);

/*
** parser_ambiguous.c
*/
char	*ft_parser_check_ambiguous(t_node *ast, char *errormsg, int state);

#endif

