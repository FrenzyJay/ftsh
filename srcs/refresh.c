/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 20:03:25 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/25 17:42:53 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "libft.h"
#include "readline.h"

static void		clear(t_entry *user);

/*
** Add character key to *cmd and put it on the terminal
*/

void			put_cmd(t_entry *user)
{
	int				cols;
	int				k;
	int				i;

	cols = get_cols();
	clear(user);
	k = 0;
	i = 0;
	while (user->current->cmd[i] != '\0')
	{
		if ((user->lines == 1 && (k + user->plen) >= cols)
				|| (user->lines > 1 && k >= cols))
		{
			tputs(tgetstr("do", NULL), 1, tputs_char);
			user->lines++;
			k = 0;
		}
		write(1, &user->current->cmd[i], 1);
		i++;
		k++;
	}
}

/*
** Return the terminal cols number
*/

int				get_cols(void)
{
	struct ttysize	term;

	ioctl(0, TIOCGWINSZ, &term);
	return (term.ts_cols);
}

/*
** Clear the actual entry
*/

static void		clear(t_entry *user)
{
	int			i;

	i = 0;
	while (i < user->lines)
	{
		tputs(tgetstr("dl", NULL), 1, tputs_char);
		if (i + 1 < user->lines)
			tputs(tgetstr("up", NULL), 1, tputs_char);
		i++;
	}
	tputs(tgetstr("cr", NULL), 1, tputs_char);
	put_prompt();
	user->lines = 1;
}
