/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 15:04:43 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 00:53:54 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <signal.h>
#include <sys/wait.h>

void	ft_sigchld(void)
{
	int		status;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		ft_putendl("FDP");
	}
}

void	ft_sigint(void)
{
	ft_putendl("sigkill catch");
}

void	ft_sigtstp(void)
{
	ft_putendl("sigstop catch");
}

void	ft_sig_handler(int c)
{
	if (c == SIGINT)
		ft_sigint();
	else if (c == SIGTSTP)
		ft_sigtstp();
	else if (c == SIGCHLD)
		ft_sigchld();
}
