/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 06:03:16 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 05:19:17 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

char			*ft_strsuck(char **str, unsigned long len)
{
	unsigned long	restlen;
	char			*sucked_string;
	char			*restof_string;

	if (!*str)
		return (NULL);
	restlen = ft_strlen(*str) - len;
	sucked_string = (char *)ft_memalloc(len + 1);
	restof_string = (char *)ft_memalloc(restlen + 1);
	sucked_string = ft_strncpy(sucked_string, *str, len);
	restof_string = ft_strcpy(restof_string, *str + len);
	ft_memdel((void **)str);
	*str = restof_string;
	return (sucked_string);
}

t_lex			*ft_lex_push(t_lex *lex, t_tok token, char *value)
{
	t_lex	*new;

	new = (t_lex *)ft_memalloc(sizeof(t_lex));
	new->token = token;
	new->value = value;
	new->prev = NULL;
	new->next = NULL;
	if (lex)
	{
		new->next = lex;
		lex->prev = new;
	}
	return (new);
}

void			ft_lex_destroy(t_lex **lex)
{
	if (!lex || !*lex)
		return ;
	if ((*lex)->next)
		ft_lex_destroy(&((*lex)->next));
	ft_memdel((void **)lex);
}

static int		ft_search_until_token(char *entry)
{
	int		i;
	int		parenth;
	char	quote;

	if ((i = ft_is_tok(entry)) > 0)
		return (i);
	parenth = quote = i = 0;
	while (entry && entry[i])
	{
		if (quote == 0 && ft_is_tok(entry + i) && !parenth)
			return (i);
		if (entry[i] == '\\' && !parenth)
			i++;
		else if ((FT_ISQUOTE(entry[i])) && quote == 0 && !parenth)
			quote = entry[i];
		else if ((FT_ISQUOTE(entry[i])) && quote != 0 && !parenth)
			quote = 0;
		else if (entry[i] == '(')
			parenth++;
		else if (entry[i] == ')')
			parenth--;
		i++;
	}
	return (i);
}

t_lex			*ft_lexer(char *entry, t_lex *lex)
{
	int		i;
	char	*tokval;
	t_tok	tok;

	if (entry && !*entry)
		ft_memdel((void **)&entry);
	if (!entry || !*entry)
		return (lex);
	i = ft_search_until_token(entry);
	tokval = ft_strsuck(&entry, i);
	tok = ft_get_tok(tokval);
	lex = ft_lexer(entry, lex);
	if (TOK_IS_RE(tok) && lex && lex->token == tok_expr)
	{
		lex->token = tok;
		ft_memdel((void **)&tokval);
	}
	else if (tok == tok_separator)
		ft_memdel((void **)&tokval);
	else
		lex = ft_lex_push(lex, tok, tokval);
	return (lex);
}

