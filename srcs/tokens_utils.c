/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 09:10:05 by garm              #+#    #+#             */
/*   Updated: 2014/03/18 14:43:47 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	quote;

	i = 0;
	quote = 0;
	while (value && value[i])
	{
		if (value[i] == '\\')
			i++;
		else if ((FT_ISQUOTE(value[i]) || value[i] == '(') && quote == 0)
			quote = value[i];
		else if ((FT_ISQUOTE(value[i]) || value[i] == ')') && quote != 0)
			quote = 0;
		i++;
	}
	if (quote == 0 && value[0] != ')')
		return (0);
	else
		return (1);
}

