/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 20:03:25 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 19:41:48 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "libft.h"
#include "readline.h"

int				get_cols(void)
{
	struct ttysize	term;

	ioctl(0, TIOCGWINSZ, &term);
	return (term.ts_cols);
}

static void		clear(void)
{
	tputs(tgetstr("rc", NULL), 1, tputs_char);
	tputs(tgetstr("cr", NULL), 1, tputs_char);
	tputs(tgetstr("cd", NULL), 1, tputs_char);
	put_prompt();
}

static void		replace_cursor(t_entry *user)
{
	int			i;

	i = user->current->clen;
	while (i > user->cursor)
	{
		move_left(user);
		i--;
	}
}

void			put_cmd(t_entry *user)
{
	clear();
	ft_putstr(user->current->cmd);
	replace_cursor(user);
}
