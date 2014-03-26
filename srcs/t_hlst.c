/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 13:33:23 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/25 17:43:14 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "readline.h"

t_hlst			*hlst_new(char *cmd)
{
	t_hlst		*new;

	if ((new = malloc(sizeof(t_hlst))) == NULL)
		return (NULL);
	new->cmd = cmd;
	new->clen = ft_strlen(cmd);
	new->lines = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			hlst_push_front(t_hlst **ahlst, t_hlst *new)
{
	if (*ahlst && new)
	{
		(*ahlst)->prev = new;
		new->next = *ahlst;
		*ahlst = new;
	}
	else
		*ahlst = new;
}

void			hlst_push_back(t_hlst **ahlst, t_hlst *new)
{
	t_hlst		*run;

	if (*ahlst && new)
	{
		run = *ahlst;
		while (run->next)
			run = run->next;
		run->next = new;
		new->prev = run;
	}
	else
		*ahlst = new;
}
