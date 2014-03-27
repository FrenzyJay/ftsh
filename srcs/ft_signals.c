/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 15:04:43 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 19:29:26 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "ftsh.h"

static void	ft_sigchld(void)
{
	int		status;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		ft_putendl("FDP");
	}
}

static void	ft_sigint(void)
{
	ft_putendl("sigkill catch");
}

static void	ft_sigtstp(void)
{
	ft_putendl("sigstop catch");
}

void		signals_inhibit()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void		ft_signal_handler(int c)
{
	if (c == SIGINT)
		ft_sigint();
	else if (c == SIGTSTP)
		ft_sigtstp();
	else if (c == SIGCHLD)
		ft_sigchld();
}
void		signals_switch()
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGTERM, ft_signal_handler);
	signal(SIGTSTP, ft_signal_handler);
	signal(SIGCONT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
}

