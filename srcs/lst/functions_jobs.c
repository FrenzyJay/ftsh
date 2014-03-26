/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_jobs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 17:50:11 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/26 18:07:26 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <unistd.h>

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

t_job	*ft_swap(t_job **lst)
{
	t_job	*tmp;

	ft_putstr("####################\n");
	ft_putstr("> courant : ");
	ft_putnbr((*lst)->num);
	ft_putstr("\n prev : ");
	if ((*lst)->prev == NULL)
			ft_putstr("NULL");
	else
		ft_putnbr((*lst)->prev->num);
	ft_putstr("    next :");
	if ((*lst)->next == NULL)
			ft_putstr("NULL");
	else
		ft_putnbr((*lst)->next->num);
	tmp = *lst;
	*lst = (*lst)->next;
//	ft_putnbr((*lst)->num);
//	ft_putchar(' ');
	(*lst)->prev = tmp->prev;
	tmp->next = (*lst)->next;
	tmp->prev = *lst;
	if ((*lst)->next != NULL)
		(*lst)->next->prev = tmp;
	(*lst)->next = tmp;
	ft_putstr("\n\n> Debut liste : ");
	ft_putnbr((*lst)->num);
	ft_putstr("\n prev : ");
	if ((*lst)->prev == NULL)
			ft_putstr("NULL");
	else
		ft_putnbr((*lst)->prev->num);
	ft_putstr("    next :");
	if ((*lst)->next == NULL)
			ft_putstr("NULL");
	else
		ft_putnbr((*lst)->next->num);
	ft_putstr("\n####################\n");
	return (*lst);
}

t_job	*ft_sort_list_asc(t_job *lst)
{
	t_job	*cursor;
	int		i;
	t_job	*begin;
//	char	test;

//	test = 0;
	i = 0;
//	begin = lst;
	cursor = lst;
	while (cursor->next != NULL)
	{
		ft_putstr("cursor->num : ");
		ft_putnbr(cursor->num);
		ft_putstr(" cursor->next->num : ");
		ft_putnbr(cursor->next->num);
		ft_putstr("\n\n");
		if (cursor->num > cursor->next->num)
		{
			ft_putstr("(cursor) ");
			ft_putnbr(cursor->num);
			//if (i == 0)
			lst = lst->next;
				begin = ft_swap(&cursor);
			cursor = begin;
			//ft_putstr(";1%");
			//ft_putchar(' ');
			i++;
		}
		else
		{
			ft_putnbr(i);
			cursor = cursor->next;
		}
		//ft_putstr(";2%");
		//ft_putnbr(cursor->num);
		//ft_putchar(' ');
		ft_putchar('\n');
	}
	return (lst);
}

int		ft_job_completed(t_job *job)
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
