/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 14:17:21 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/24 22:22:16 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_command_process(char **argv)
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

void		ft_viewlist_process(t_process *list)
{
	t_process	*cursor;
	char		*stateM[4];
	int			index;

	if (!list)
		return ;
	stateM[0] = " done      ";
	stateM[1] = " suspended ";
	stateM[2] = " running   ";
	stateM[3] = " continued ";
	cursor = list;
	while (42)
	{
		ft_putnbr(cursor->pid);
		index = cursor->state;
		ft_putstr(stateM[index]);
		ft_command_process(cursor->argv);
		ft_putchar('\n');
		if (cursor->next == NULL)
			return ;
		else
			cursor = cursor->next;
	}
}

t_process	*ft_create_process(pid_t pid, char **argv)
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
	return (new);
}

void	ft_add_process(t_process **list, pid_t pid, char **argv)
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
