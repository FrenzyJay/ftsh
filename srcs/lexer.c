/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 06:03:16 by garm              #+#    #+#             */
/*   Updated: 2014/03/16 13:48:26 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_lex	*ft_lexer(char *entry, t_lex *lextable, t_lex *prev_tok)
{
	if (!entry || !*entry)
		return (lextable);
	return (lextable);
	(void)prev_tok;
}

