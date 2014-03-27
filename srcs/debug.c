/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 14:40:08 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 19:32:36 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

char	*ft_toktostr(t_tok token)
{
	char	*str[NB_TOKENS];

	str[0] = "SEPARATOR";
	str[1] = "UNCOMPLETED";
	str[2] = "EXPR";
	str[3] = "HEREDOC";
	str[4] = "READ";
	str[5] = "WRITE";
	str[6] = "APPEND";
	str[7] = "CMD";
	str[8] = "ARG";
	str[9] = "PIPE";
	str[10] = "AND";
	str[11] = "OR";
	str[12] = "SUBSH";
	str[13] = "END";
	str[14] = "BG";
	return (str[token]);
}

void	ft_putlex(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		ft_putstr("{");
		ft_putstr(ft_toktostr(tmp->token));
		ft_putstr("} -> [");
		ft_putstr(tmp->value);
		ft_putendl("]");
		tmp = tmp->next;
	}
}
