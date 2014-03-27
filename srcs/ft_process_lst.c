/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 14:17:21 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 19:28:57 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ftsh.h"

static void			ft_command_process(char **argv)
{
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			ft_putchar(argv[i][j]);
			j++;
		}
		ft_putchar(' ');
		i++;
	}
}

static void			ft_view_info_process(t_process *cursor)
{
	char		*state_m[5];
	int			index;

	state_m[0] = " done       ";
	state_m[1] = " suspended  ";
	state_m[2] = " running    ";
	state_m[3] = " continued  ";
	state_m[4] = " terminated ";
	ft_putnbr(cursor->pid);
	index = cursor->state;
	ft_putstr(state_m[index]);
	ft_command_process(cursor->argv);
}

void				ft_viewlist_process(t_process *list)
{
	t_process	*cursor;

	if (!list)
		return ;
	cursor = list;
	while (42)
	{
		ft_view_info_process(cursor);
		if (cursor->next == NULL)
		{
			ft_putchar('\n');
			return ;
		}
		else
		{
			ft_putstr(" |\n       ");
			cursor = cursor->next;
		}
	}
}

static t_process	*ft_create_process(pid_t pid, char **argv)
{
	t_process	*new;

	new = (t_process *)malloc(sizeof(t_process));
	if (new)
	{
		new->pid = pid;
		new->argv = argv;
		new->state = 2;
		new->completed = 0;
		new->stopped = 0;
		new->next = NULL;
	}
	else
		return (NULL);
	return (new);
}

void				ft_add_process(t_process **list, pid_t pid, char **argv)
{
	t_process	*new;
	t_process	*cursor;

	new = ft_create_process(pid, argv);
	if (new)
	{
		if (!*list)
			*list = new;
		else
		{
			cursor = *list;
			while (cursor->next != NULL)
				cursor = cursor->next;
			cursor->next = new;
		}
	}
}
