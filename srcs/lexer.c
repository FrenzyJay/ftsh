/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 06:03:16 by garm              #+#    #+#             */
/*   Updated: 2014/03/18 06:03:10 by garm             ###   ########.fr       */
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
	sucked_string = ft_strcpy(sucked_string, *str + len);
	ft_memdel((void **)str);
	*str = restof_string;
	return (sucked_string);
}

t_lex			*ft_lex_push(t_lex *lex, t_tok token, char *value)
{
	t_lex	*new;

	if (!value || !*value)
		return (lex);
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
	ft_memdel((void **)&((*lex)->value));
	ft_memdel((void **)lex);
}

static int		ft_search_until_token(char *entry)
{
	int		i;
	char	quote;

	if ((i = ft_is_tok(entry)) > 0)
		return (i);
	i = 0;
	quote = 0;
	while (entry && entry[i])
	{
		if (quote == 0 && ft_is_tok(entry + i))
			return (i);
		if (entry[i] == '\\')
			i++;
		else if ((FT_ISQUOTE(entry[i]) || entry[i] == '(') && quote == 0)
			quote = entry[i];
		else if ((FT_ISQUOTE(entry[i]) || entry[i] == ')') && quote != 0)
			quote = 0;
		i++;
	}
	return (i);
}

t_lex			*ft_lexer(char *entry, t_lex *lex)
{
	int		i;
	char	*tokval;
	t_tok	tok;

	if (!entry || !*entry)
		return (lex);
	i = ft_search_until_token(entry);
	tokval = ft_strsuck(&entry, i);
	tok = ft_get_tok(tokval);
	lex = ft_lexer(entry, lex);
	if (FT_TOK_IS_REDIRECTION(tok) && lex->next && lex->next->token == TOK_EXPR)
	{
		ft_memdel((void **) &(lex->value));
		lex->value = tokval;
		lex->token = tok;
	}
	else
		lex = ft_lex_push(lex, tok, tokval);
	return (lex);
}

