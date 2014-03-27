/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_jobs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 17:50:11 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 19:29:58 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftsh.h"

void		ft_determine_recent(t_job **list)
{
	t_job	*cursor;
	int		i;

	if (*list == NULL)
		return ;
	cursor = *list;
	i = 0;
	while (42)
	{
		if (i == 0)
			cursor->recent = '+';
		else if (i == 1)
			cursor->recent = '-';
		else
			cursor->recent = ' ';
		i++;
		if (cursor->next == NULL)
			return ;
		else
			cursor = cursor->next;
	}
}

int			ft_min_num_job(t_job *lst)
{
	int		min;
	t_job	*cursor;

	min = 1;
	if (!lst)
		return (min);
	cursor = lst;
	while (42)
	{
		if (cursor->num >= min)
		{
			min = cursor->num + 1;
			cursor = lst;
		}
		if (cursor->next != NULL)
			cursor = cursor->next;
		else
			break ;
	}
	return (min);
}

int			ft_max_num_job(t_job *lst)
{
	int		max;
	t_job	*cursor;

	max = 0;
	if (!lst)
		return (0);
	cursor = lst;
	while (42)
	{
		if (cursor->num >= max)
			max = cursor->num;
		if (cursor->next != NULL)
			cursor = cursor->next;
		else
			break ;
	}
	return (max);
}

int			ft_job_completed(t_job *job)
{
	t_process	*process;

	process = job->first_process;
	while (42)
	{
		if (process->completed == 0)
			return (0);
		if (process->next == NULL)
			break ;
		else
			process = process->next;
	}
	return (1);
}
