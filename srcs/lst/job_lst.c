/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 17:03:43 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/26 00:21:00 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void		ft_print_num_job(int i)
{
	ft_putchar('[');
	ft_putnbr(i);
	ft_putchar(']');
	if (i < 10)
		ft_putchar(' ');
	ft_putchar(' ');
}

void		ft_viewlist_job(t_job *lstjob)
{
	t_job		*curs_j;

	if (!lstjob)
		return ;
//	curs_j = lstjob;
	curs_j = ft_sort_list_asc(lstjob);
	while (42)
	{
		ft_print_num_job(curs_j->num);
		ft_putchar(curs_j->recent);
		ft_putchar(' ');
		ft_viewlist_process(curs_j->first_process);
		if (curs_j->next == NULL)
			break ;
		else
			curs_j = curs_j->next;
	}
}

t_job		*ft_create_job(t_job **lst_j, pid_t *tab_p, int size, char *cmd)
{
	t_job		*new;
	t_process	*process;
	int			i;
	char		**cmd_p;
	char		**cmd_opt_p;

	cmd_p = ft_strsplit(cmd, '|');
	i = 0;
	process = NULL;
	new = (t_job *)malloc(sizeof(t_job));
	if (new)
	{
		new->num = ft_min_num_job(*lst_j);
		new->recent = '+';
		while (i < size)
		{
			cmd_opt_p = ft_strsplit(cmd_p[i], ' ');
			ft_add_process(&process, tab_p[i], cmd_opt_p);
			i++;
		}
		new->first_process = process;
		new->pgid = getpgid(tab_p[0]);
		new->command = cmd;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void		ft_add_job(t_job **lst_j, pid_t *process, int size, char *cmd)
{
	t_job	*new;

	new = ft_create_job(lst_j, process, size, cmd);
	if (new)
	{
		if (!lst_j)
			*lst_j = new;
		else
		{
			new->next = *lst_j;
			(*lst_j)->prev = new;
			*lst_j = new;
/*			if (new->next != NULL)
			{
				new->next->recent = ' ';
				if (new->next->next != NULL)
					new->next->next->recent = ' ';
					}*/
			//ft_determine_recent(lst_j);
		}
	}
}
