/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 07:13:19 by garm              #+#    #+#             */
/*   Updated: 2014/03/18 02:55:50 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "42sh.h"

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
	ft_set_tokval(tokvals[11], TOK_END, "&");
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

int				ft_is_tok(char *entry)
{
	t_tokval	**tvals;
	int			i;
	int			ret;

	if (!entry || !*entry)
		return (0);
	if (entry[0] == ' ' || entry[0] == '\t')
		return (ft_getsize_separator(entry));
	tvals = ft_get_tokvals();
	i = 0;
	while (i < NB_TOKVALS)
	{
		if (ft_strncmp(entry, tvals[i]->value, ft_strlen(tvals[i]->value)) == 0)
		{
			ret = ft_strlen(tvals[i]->value);
			ft_del_tokvals(&tvals);
			return (ret);
		}
		i++;
	}
	ft_del_tokvals(&tvals);
	return (0);
}

t_tok	ft_get_tok(char *tval)
{
	t_tokval	**tvals;
	int			i;
	t_tok		ret;

	tvals = ft_get_tokvals();
	i = 0;
	while (i < NB_TOKVALS)
	{
		if (ft_strncmp(tval, tvals[i]->value, ft_strlen(tvals[i]->value)) == 0)
		{
			ret = tvals[i]->token;
			ft_del_tokvals(&tvals);
			return (ret);
		}
		i++;
	}
	ft_del_tokvals(&tvals);
	if (ft_is_uncompleted(tval))
		return (ret = TOK_UNCOMPLETED);
	else
		return (ret = TOK_EXPR);
}

