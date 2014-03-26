/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:50:11 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/26 15:50:55 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

/*
** Signals inhibiter
*/
void	signals_inhibit()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

/*
** Signals switch
*/
void	signals_switch()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

