/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_stop_cont_job.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 23:58:41 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/24 23:59:46 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include <unistd.h>

void	ft_check_process_tostop(t_process **lstprocess)
{
	t_process	*cursor;

	cursor = *lstprocess;
	while (42)
	{
		if (cursor->state == 1)
			break ;
		else if (cursor->state == 2 || cursor->state == 3)
		{
			kill(cursor->pid, SIGTSTP);
			cursor->state = 1;
		}
		if (cursor->next == NULL)
			break ;
		else
			cursor = cursor->next;
	}
}

void	ft_stop_job(t_job **lstjob, pid_t pgid)
{
	t_job	*cursor_job;

	if (!lstjob)
		return ;
	cursor_job = *lstjob;
	while (42)
	{
		if (cursor_job->pgid == pigd)
		{
			if (cursor_job->first_process == NULL)
				return ;
			ft_check_process_tostop(&(cursor_job->first_process));
		}
		if (cursor_job->next == NULL)
			break ;
		else
			cursor_job = cursor_job->next;
	}
}

void	ft_check_process_tocont(t_process **lstprocess)
{
	t_process	*cursor;

	cursor = *lstprocess;
	while (42)
	{
		if (cursor->state == 1)
			break ;
		else if (cursor->state == 1)
		{
			kill(cursor->pid, SIGCONT);
			cursor->state = 3;
		}
		if (cursor->next == NULL)
			break ;
		else
			cursor = cursor->next;
	}
}

void	ft_cont_job(t_job **lstjob, pid_t pgid)
{
	t_job	*cursor_job;

	if (!lstjob)
		return ;
	cursor_job = *lstjob;
	while (42)
	{
		if (cursor_job->pgid == pigd)
		{
			if (cursor_job->first_process == NULL)
				return ;
			ft_check_process_tocont(&(cursor_job->first_process));
		}
		if (cursor_job->next == NULL)
			break ;
		else
			cursor_job = cursor_job->next;
	}
}
