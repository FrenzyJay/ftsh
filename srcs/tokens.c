/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 07:13:19 by garm              #+#    #+#             */
/*   Updated: 2014/03/18 10:11:54 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "42sh.h"

static t_tokval		*ft_set_tokval(t_tok token, char *value)
{
	t_tokval	*new_tokval;

	new_tokval = (t_tokval *)malloc(sizeof(t_tokval));
	new_tokval->token = token;
	new_tokval->value = value;
	return (new_tokval);
}

static t_tokval		**ft_get_tokvals(void)
{
	t_tokval	**tokvals;

	tokvals = (t_tokval **)malloc(sizeof(t_tokval *) * NB_TOKVALS);
	tokvals[0] = ft_set_tokval(TOK_HEREDOC, "<<");
	tokvals[1] = ft_set_tokval(TOK_APPEND, ">>");
	tokvals[2] = ft_set_tokval(TOK_AND, "&&");
	tokvals[3] = ft_set_tokval(TOK_OR, "||");
	tokvals[4] = ft_set_tokval(TOK_SEPARATOR, " ");
	tokvals[5] = ft_set_tokval(TOK_SEPARATOR, "\t");
	tokvals[6] = ft_set_tokval(TOK_READ, "<");
	tokvals[7] = ft_set_tokval(TOK_WRITE, ">");
	tokvals[8] = ft_set_tokval(TOK_PIPE, "|");
	tokvals[9] = ft_set_tokval(TOK_END, ";");
	tokvals[10] = ft_set_tokval(TOK_END, "\n");
	tokvals[11] = ft_set_tokval(TOK_BG, "&");
	return (tokvals);
}

static void			ft_del_tokvals(t_tokval ***tokvals)
{
	int		i;

	i = 0;
	ft_putendl("DELETE ALL");
	while (i < NB_TOKVALS)
	{
		printf("%s\n", (**tokvals + i)->value);
		if (**tokvals + i)
			free(**tokvals + i);
		i++;
	}
	free(*tokvals);
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

