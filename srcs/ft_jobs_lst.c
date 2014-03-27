/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 17:03:43 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 04:46:09 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "42sh.h"

static void		ft_view_info_job(t_job *curs_j)
{
	ft_putchar('[');
	ft_putnbr(curs_j->num);
	ft_putchar(']');
	if (curs_j->num < 10)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putchar(curs_j->recent);
	ft_putchar(' ');
	ft_viewlist_process(curs_j->first_process);
}

void			ft_viewlist_job(t_job *lstjob)
{
	t_job		*curs_j;
	int			max;
	int			i;

	if (!lstjob)
		return ;
	i = 0;
	curs_j = lstjob;
	max = ft_max_num_job(lstjob);
	while (i <= max)
	{
		if (curs_j->num == i)
		{
			ft_view_info_job(curs_j);
			curs_j = lstjob;
			i++;
		}
		else
		{
			if (curs_j->next == NULL)
				i++;
			else
				curs_j = curs_j->next;
		}
	}
}

static t_job	*ft_create_job(t_job **lst_j, pid_t *tab_p, t_process *process)
{
	t_job		*new;

	new = (t_job *)malloc(sizeof(t_job));
	if (new)
	{
		new->num = ft_min_num_job(*lst_j);
		new->first_process = process;
		new->pgid = getpgid(tab_p[0]);
		new->next = NULL;
		new->prev = NULL;
	}
	else
		return (NULL);
	return (new);
}

void			ft_add_job(t_job **lst_j, pid_t *pid, t_process *process)
{
	t_job		*new;

	new = ft_create_job(lst_j, pid, process);
	if (new)
	{
		if (*lst_j == NULL)
			*lst_j = new;
		else
		{
			new->next = *lst_j;
			(*lst_j)->prev = new;
			*lst_j = new;
			ft_determine_recent(lst_j);
		}
	}
}

