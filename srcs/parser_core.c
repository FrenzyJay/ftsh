/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/20 04:46:51 by garm              #+#    #+#             */
/*   Updated: 2014/03/20 09:30:05 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

t_node	*ft_parse_end(t_lex *head, t_node *tree)
{
	t_lex	*tail;

	if (!head)
		return (tree);
	tail = ft_parser_find2(head, NULL, TOK_END, TOK_BG);
	tree = ft_parse_logic(head, tail, tree);
	tree = ft_ast_add(tree, tail, 'L');
	return (ft_parse_end(tail->next, tree));
}

t_node	*ft_parse_logic(t_lex *head, t_lex *tail, t_node *tree)
{
	t_lex	*logic_ope;

	if (!head)
		return (tree);
	logic_ope = ft_parser_find2(head, tail, TOK_AND, TOK_OR);
	tree = ft_parse_pipeline(head, logic_ope, tree, 0);
	tree = ft_ast_add(tree, logic_ope, 'L');
	return (ft_parse_logic(logic_ope->next, tail, tree));
}

t_node	*ft_parse_pipeline(t_lex *head, t_lex *tail, t_node *tree, int ktr)
{
	t_lex	*pipeline_ope;
	t_lex	*next_pipe;

	ktr++;
	if (!head)
		return (tree);
	pipeline_ope = ft_parser_find(head, tail, TOK_PIPE);
	if (!pipeline_ope)
		return (tree);
	tree = ft_parse_pipeline(pipeline_ope->next, tail, tree, ktr);
	tree = ft_ast_add(tree, pipeline_ope, 'L');
	next_pipe = ft_parser_find(pipeline_ope->next, tail, TOK_PIPE);
	ft_parse_redirections(pipeline_ope, next_pipe, tree, 'R');
	if (ktr == 1)
		return (ft_parse_redirections(head, pipeline_ope, tree, 'L'));
	return (tree);
}

t_node	*ft_parse_redirections(t_lex *head, t_lex *tail, t_node *tree, int side)
{
	return (NULL);
	(void)head;
	(void)tail;
	(void)tree;
	(void)side;
}

