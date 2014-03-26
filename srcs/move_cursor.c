/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 20:14:08 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/26 20:41:15 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <termcap.h>
#include "readline.h"

void		move_right(t_entry *user)
{
	if ((user->cursor + user->plen + 1) % get_cols() == 0)
		tputs(tgetstr("do", NULL), 1, tputs_char);
	else
		tputs(tgetstr("nd", NULL), 1, tputs_char);
}

void		move_left(void)
{
	tputs(tgetstr("le", NULL), 1, tputs_char);
}
