/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 22:31:36 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/26 23:16:18 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "lst.h"

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
