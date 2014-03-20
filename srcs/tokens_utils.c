/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 09:10:05 by garm              #+#    #+#             */
/*   Updated: 2014/03/20 04:11:34 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

int		ft_getsize_separator(char *entry)
{
	int		i;

	i = 0;
	while (entry[i] && (entry[i] == ' ' || entry[i] == '\t'))
		i++;
	return (i);
}

int		ft_is_uncompleted(char *value)
{
	int		i;
	int		parenth;
	char	quote;

	i = 0;
	parenth = 0;
	quote = 0;
	while (value && value[i])
	{
		if (value[i] == '\\')
			i++;
		else if ((FT_ISQUOTE(value[i])) && quote == 0 && !parenth)
			quote = value[i];
		else if ((FT_ISQUOTE(value[i])) && quote != 0 && !parenth)
			quote = 0;
		else if (value[i] == '(')
			parenth++;
		else if (value[i] == ')')
			parenth--;
		i++;
	}
	if (quote == 0 && value[0] != ')')
		return (0);
	else
		return (1);
}

t_lex	*ft_lexer_end(t_lex *lex)
{
	t_lex	*tmp;
	t_lex	*new;

	if (!lex)
		return (NULL);
	tmp = lex;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp->token != TOK_BG && tmp->token != TOK_END)
	{
		new = (t_lex *)ft_memalloc(sizeof(t_lex));
		new->token = TOK_END;
		new->value = ft_strdup(";");
		new->next = NULL;
		new->prev = tmp;
		tmp->next = new;
	}
	return (lex);
}

