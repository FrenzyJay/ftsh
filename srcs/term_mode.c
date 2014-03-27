/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/02 11:46:44 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 19:42:38 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <termcap.h>
#include <stdlib.h>
#include "libft.h"
#include "readline.h"

static void			get_termcap(void)
{
	char			*termtype;
	char			buffer[2048];
	int				ret;

	if ((termtype = getenv("TERM")) == 0)
	{
		ft_putstr("Specify a terminal type `setenv TERM <yourtype>`.");
		exit(1);
	}
	ret = tgetent(buffer, termtype);
	if (ret < 0)
	{
		ft_putstr("Could not acces the termcap database.");
		exit(1);
	}
	if (ret == 0)
	{
		ft_putstr(termtype);
		ft_putstr(": terminal type is not defined.");
		exit(1);
	}
}

void				raw_term_mode(void)
{
	struct termios	term;

	get_termcap();
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &term);
}

void				default_term_mode(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &term);
}
