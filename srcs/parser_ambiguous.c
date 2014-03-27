/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_ambiguous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 10:27:26 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 17:10:39 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

static int	ft_browse_2(t_node *cursor, int state)
{
	while (cursor)
	{
		if (TOK_IS_RIGHT_RE(cursor->token))
			return (STATE_ERROR_OUTPUT);
		else if (TOK_IS_LEFT_RE(cursor->token))
			return (STATE_ERROR_INPUT);
		cursor = cursor->right;
	}
	return (state);
}

static int	ft_browse(t_node *cursor, int mode, int state)
{
	if (mode == 0)
	{
		while (cursor)
		{
			if (TOK_IS_LEFT_RE(cursor->token))
				return (STATE_ERROR_INPUT);
			cursor = cursor->right;
		}
	}
	else if (mode == 1)
	{
		while (cursor)
		{
			if (TOK_IS_RIGHT_RE(cursor->token))
				return (STATE_ERROR_OUTPUT);
			cursor = cursor->right;
		}
	}
	else
		return (ft_browse_2(cursor, state));
	return (state);
}

static int	ft_update_pipe_state(t_node *ast, int state)
{
	if ((!ast->parent || ast->parent->token != tok_pipe))
	{
		state = ft_browse(ast, 0, state);
		state = ft_browse(ast->left, 1, state);
	}
	else if (ast->parent->token == tok_pipe && ast->left->token == tok_pipe)
		state = ft_browse(ast, 2, state);
	else if (ast->parent->token == tok_pipe && ast->left->token != tok_pipe)
	{
		state = ft_browse(ast->left, 1, state);
		state = ft_browse(ast, 2, state);
	}
	return (state);
}

static int	ft_update_state(t_node *ast, t_tok token, int state)
{
	if (TOK_IS_LOGIC(token) || TOK_IS_END(token))
		state = STATE_RW;
	if (TOK_IS_LEFT_RE(token))
	{
		if (state == STATE_WRITE)
			state = state - STATE_RW;
		else
			state = state - STATE_READ;
	}
	if (TOK_IS_RIGHT_RE(token))
	{
		if (state == STATE_READ)
			state = state - STATE_RW;
		else
			state = state - STATE_WRITE;
	}
	if (token == tok_pipe)
		state = ft_update_pipe_state(ast, state);
	return (state);
}

char		*ft_parser_check_ambiguous(t_node *ast, char *errormsg, int state)
{
	if (state == -1)
		errormsg = "Ambiguous input redirect.";
	else if (state == -2)
		errormsg = "Ambiguous output redirect.";
	else if (state < -2)
		errormsg = "Ambiguous redirect.";
	if (errormsg)
		return (errormsg);
	if (ast)
	{
		state = ft_update_state(ast, ast->token, state);
		errormsg = ft_parser_check_ambiguous(ast->right, errormsg, state);
		errormsg = ft_parser_check_ambiguous(ast->left, errormsg, state);
		return (errormsg);
	}
	return (errormsg);
}

