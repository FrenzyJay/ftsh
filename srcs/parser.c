/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/20 03:42:51 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 10:02:27 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

t_node		*ft_parser(char *entry)
{
	t_lex	*lex;
	t_node	*tree;
	char	*error;

	if (!entry)
		return (NULL);
	lex = ft_lexer(entry, NULL);
	lex = ft_lexer_end(lex);
	tree = ft_parse_end(lex, NULL);
	ft_lex_destroy(&lex);
	tree = ft_ast_rewind(tree);
	error = ft_parser_check_error(tree);
	if (error)
	{
		ft_ast_destroy(&tree);
		return (NULL);
	}
	return (tree);
}

t_lex		*ft_parser_find(t_lex *head, t_lex *tail, t_tok tok)
{
	if (!head)
		return (NULL);
	while (head && head->token != tok && head != tail)
		head = head->next;
	if (head->token == tok)
		return (head);
	else
		return (NULL);
}

t_lex		*ft_parser_find2(t_lex *head, t_lex *tail, t_tok tok1, t_tok tok2)
{
	if (!head)
		return (NULL);
	while (head && head->token != tok1 && head->token != tok2 && head != tail)
		head = head->next;
	if (head->token == tok1 || head->token == tok2)
		return (head);
	else
		return (NULL);
}

