/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 16:12:28 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 18:20:34 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

static int		ft_check_pipe(t_node *ast)
{
	if (!ast)
		return (0);
	if (ast->left && ast->right)
	{
		if (CHECK_PIPE(ast->left->token) || ast->left->token == tok_pipe)
		{
			if (CHECK_PIPE(ast->right->token))
				return (1);
		}
	}
	return (0);
}

static char		*ft_is_error_redirection(t_node *ast)
{
	t_node	*cursor;
	int		presence_expr;

	presence_expr = 0;
	if (ast && TOK_IS_RE(ast->token))
	{
		cursor = ast;
		while (cursor)
		{
			if (cursor->token == tok_expr || cursor->token == tok_subsh)
			{
				presence_expr = 1;
				break ;
			}
			cursor = cursor->right;
		}
	}
	else
		return (NULL);
	if (presence_expr)
		return (NULL);
	else if (ast && TOK_IS_RE(ast->token))
		return (ast->value);
	else
		return ("NULL");
}

static char		*ft_is_error(t_node *ast)
{
	if (ast->token == tok_pipe && !ft_check_pipe(ast))
		return (ast->value);
	if (ast->parent)
	{
		if (ast->token == tok_expr && CHECK_EXPR_PARENT(ast->parent->token))
			return (ast->value);
		if (TOK_IS_RE(ast->token) && CHECK_RE_PARENT(ast->parent->token))
			return (ast->value);
		if (TOK_IS_END(ast->token) && CHECK_END_PARENT(ast->parent->token))
			return (ast->value);
		if (ast->token == tok_subsh && CHECK_SUBSH_PARENT(ast->parent->token))
			return (ast->value);
		if (TOK_IS_LOGIC(ast->token) && CHECK_LOGIC_PARENT(ast->parent->token))
			return (ast->value);
		if (ast->token == tok_pipe && CHECK_PIPE_PARENT(ast->parent->token))
			return (ast->value);
	}
	else
	{
		if (ast->token == tok_bg)
			return (ast->value);
		if (TOK_IS_LOGIC(ast->token))
			return (ast->value);
	}
	return (NULL);
}

static char		*ft_parse_error(t_node *ast, char *errormsg)
{
	if (errormsg)
		return (errormsg);
	if (ast)
	{
		if (!errormsg)
			errormsg = ft_is_error_redirection(ast);
		if (!errormsg)
			errormsg = ft_is_error(ast);
		errormsg = ft_parse_error(ast->left, errormsg);
		errormsg = ft_parse_error(ast->right, errormsg);
		return (errormsg);
	}
	return (errormsg);
}

char			*ft_parser_check_error(t_node *ast)
{
	char	*tokval;
	char	*error;

	error = NULL;
	if ((tokval = ft_parse_error(ast, NULL)))
	{
		if (ft_strncmp("NULL", tokval, 4) == 0)
			ft_error("ftsh", "Invalid null command.");
		else
			ft_error("ftsh: parse error near", tokval);
		return (tokval);
	}
	if ((error = ft_parser_check_ambiguous(ast, NULL, STATE_RW)))
	{
		ft_error("ftsh", error);
		return (error);
	}
	return (NULL);
}

