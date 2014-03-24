/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 15:04:43 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/24 20:33:44 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <signal.h>

void	ft_sigint()
{
	ft_putendl("sigkill cath");
}

void	ft_sigtstp()
{
	ft_putendl("sigstop cath");
}

void	ft_sig_handler(int c)
{
	if (c == SIGINT)
		ft_sigint();
	else if (c == SIGTSTP)
		ft_sigtstp();
}