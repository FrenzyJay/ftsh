/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 14:39:35 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/23 16:18:08 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <unistd.h>

int		main(int ac, char **av)
{
	t_process	*lst;
	pid_t		ft;

	if (ac == 1)
		return (1);
	lst = NULL;
	ft = 50000;
	ft_putnbr(getpgid(51749));
	ft_putchar('\n');
	ft_add_process(&lst, ft, av);
	ft_viewlist_process(lst);
	return (0);
}
