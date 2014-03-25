/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 07:13:19 by garm              #+#    #+#             */
/*   Updated: 2014/03/25 19:55:45 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "42sh.h"

static void			ft_set_tokval(t_tokval *tokval, t_tok token, char *value)
{
	tokval->token = token;
	tokval->value = value;
}

void			ft_get_tokvals(t_tokval *tokvals)
{
	ft_set_tokval(&tokvals[0], tok_heredoc, "<<");
	ft_set_tokval(&tokvals[1], tok_append, ">>");
	ft_set_tokval(&tokvals[2], tok_and, "&&");
	ft_set_tokval(&tokvals[3], tok_or, "||");
	ft_set_tokval(&tokvals[4], tok_separator, " ");
	ft_set_tokval(&tokvals[5], tok_separator, "\t");
	ft_set_tokval(&tokvals[6], tok_read, "<");
	ft_set_tokval(&tokvals[7], tok_write, ">");
	ft_set_tokval(&tokvals[8], tok_pipe, "|");
	ft_set_tokval(&tokvals[9], tok_end, ";");
	ft_set_tokval(&tokvals[10], tok_end, "\n");
	ft_set_tokval(&tokvals[11], tok_bg, "&");
}

int				ft_is_tok(char *entry)
{
	t_tokval	tvals[NB_TOKVALS];
	int			i;
	int			ret;

	if (!entry || !*entry)
		return (0);
	if (entry[0] == ' ' || entry[0] == '\t')
		return (ft_getsize_separator(entry));
	ft_get_tokvals(tvals);
	i = 0;
	while (i < NB_TOKVALS)
	{
		if (ft_strncmp(entry, tvals[i].value, ft_strlen(tvals[i].value)) == 0)
		{
			ret = ft_strlen(tvals[i].value);
			return (ret);
		}
		i++;
	}
	return (0);
}

t_tok	ft_get_tok(char *tval)
{
	t_tokval	tvals[NB_TOKVALS];
	int			i;
	t_tok		ret;

	ft_get_tokvals(tvals);
	i = 0;
	while (i < NB_TOKVALS)
	{
		if (ft_strncmp(tval, tvals[i].value, ft_strlen(tvals[i].value)) == 0)
		{
			ret = tvals[i].token;
			return (ret);
		}
		i++;
	}
	if (ft_is_uncompleted(tval))
		return (ret = tok_uncompleted);
	else
		return (ret = tok_expr);
}

