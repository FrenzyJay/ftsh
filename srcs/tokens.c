/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 07:13:19 by garm              #+#    #+#             */
/*   Updated: 2014/03/16 09:08:51 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"

static void			ft_set_tokval(t_tokval *tokval, t_tok token, char *value)
{
	if (tokval)
	{
		tokval->token = token;
		tokval->value = value;
	}
}

static t_tokval		**ft_get_tokvals(void)
{
	t_tokval	**tokvals;

	tokvals = (t_tokval **)malloc(sizeof(void *) * NB_TOKVALS);
	ft_set_tokval(tokvals[0], TOK_HEREDOC, "<<");
	ft_set_tokval(tokvals[1], TOK_APPEND, ">>");
	ft_set_tokval(tokvals[2], TOK_AND, "&&");
	ft_set_tokval(tokvals[3], TOK_OR, "||");
	ft_set_tokval(tokvals[4], TOK_SEPARATOR, " ");
	ft_set_tokval(tokvals[5], TOK_SEPARATOR, "\t");
	ft_set_tokval(tokvals[6], TOK_READ, "<");
	ft_set_tokval(tokvals[7], TOK_WRITE, ">");
	ft_set_tokval(tokvals[8], TOK_PIPE, "|");
	ft_set_tokval(tokvals[9], TOK_END, ";");
	ft_set_tokval(tokvals[10], TOK_END, "\n");
	return (tokvals);
}

static void			ft_del_tokvals(t_tokval ***tokvals)
{
	if (*tokvals)
	{
		free((void *)*tokvals);
		*tokvals = NULL;
	}
}



