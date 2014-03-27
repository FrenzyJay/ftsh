/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/20 04:46:51 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 01:11:27 by garm             ###   ########.fr       */
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
	tail = ft_parser_find2(head, NULL, tok_end, tok_bg);
	tree = ft_parse_logic(head, tail, tree);
	if (!tail)
		return (tree);
	tree = ft_ast_add(tree, tail, 'L');
	return (ft_parse_end(tail->next, tree));
}

t_node	*ft_parse_logic(t_lex *head, t_lex *tail, t_node *tree)
{
	t_lex	*logic_ope;

	if (!head || head == tail)
		return (tree);
	logic_ope = ft_parser_find2(head, tail, tok_and, tok_or);
	if (!logic_ope)
	{
		tree = ft_parse_pipeline(head, tail, tree, 0);
		return (tree);
	}
	tree = ft_parse_pipeline(head, logic_ope, tree, 0);
	tree = ft_ast_add(tree, logic_ope, 'L');
	return (ft_parse_logic(logic_ope->next, tail, tree));
}

t_node	*ft_parse_pipeline(t_lex *head, t_lex *tail, t_node *tree, int ktr)
{
	t_lex	*pipeline_ope;
	t_lex	*next_pipe;

	ktr++;
	if (!head || head == tail)
		return (tree);
	pipeline_ope = ft_parser_find(head, tail, tok_pipe);
	if (!pipeline_ope && ktr == 1)
		return (ft_parse_redirections(head, tail, tree, 'L'));
	else if (!pipeline_ope)
		return (tree);
	tree = ft_parse_pipeline(pipeline_ope->next, tail, tree, ktr);
	tree = ft_ast_add(tree, pipeline_ope, 'L');
	next_pipe = ft_parser_find(pipeline_ope->next, tail, tok_pipe);
	if (pipeline_ope && ktr == 1)
	{
		ft_parse_redirections(pipeline_ope, next_pipe, tree, 'R');
		return (ft_parse_redirections(head, pipeline_ope, tree, 'L'));
	}
	return (ft_parse_redirections(pipeline_ope, next_pipe, tree, 'R'));
}

t_node	*ft_parse_redirections(t_lex *head, t_lex *tail, t_node *tree, int side)
{
	t_lex	*cursor;

	cursor = head;
	while (cursor && cursor != tail)
	{
		if (TOK_IS_REDIRECTION(cursor->token))
		{
			if (side == 'R')
				ft_ast_stack_right(tree, cursor);
			else
				tree = ft_ast_add(tree, cursor, side);
			side = 'R';
		}
		cursor = cursor->next;
		if (!(TOK_IS_REDIRECTION(cursor->token)) && (cursor->token != tok_expr))
			break ;
	}
	return (ft_parse_cmd(head, tail, tree, side));
}

t_node	*ft_parse_cmd(t_lex *head, t_lex *tail, t_node *tree, int side)
{
	t_lex	*cursor;

	cursor = head;
	while (cursor && cursor != tail)
	{
		if (cursor->token == tok_expr)
		{
			if (side == 'R')
				ft_ast_stack_right(tree, cursor);
			else
				tree = ft_ast_add(tree, cursor, side);
			side = 'R';
		}
		cursor = cursor->next;
		if (!(TOK_IS_REDIRECTION(cursor->token)) && (cursor->token != tok_expr))
			break ;
	}
	return (tree);
}

