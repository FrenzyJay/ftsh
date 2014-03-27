/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_errting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 17:32:03 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 20:30:59 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftsh.h"

void	ft_destroy_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_destroy_process(t_process **list)
{
	t_process	*tmp;
	t_process	*cursor;

	if (list == NULL)
		return ;
	cursor = *list;
	while (42)
	{
		tmp = cursor->next;
		ft_destroy_tab(cursor->argv);
		free(cursor);
		cursor = NULL;
		cursor = tmp;
		if (cursor == NULL)
			break ;
	}
	*list = NULL;
}

void	ft_destroy_job(t_job **list)
{
	t_job	*tmp;
	t_job	*cursor;

	if (list == NULL)
		return ;
	cursor = *list;
	while (42)
	{
		tmp = cursor->next;
		ft_destroy_process(&(cursor->first_process));
		free(cursor);
		cursor = NULL;
		cursor = tmp;
		if (cursor == NULL)
			break ;
	}
	*list = NULL;
}

void	ft_destroy_hlst(t_hlst *historic)
{
	if (!historic)
		return ;
	ft_destroy_hlst(historic->next);
	free(historic->cmd);
	historic->cmd = NULL;
	free(historic);
	historic = NULL;
}
