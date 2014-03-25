/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_arrows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 13:50:26 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/25 17:40:45 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <stdlib.h>
#include "libft.h"
#include "readline.h"

void		key_right(t_entry *user)
{
	if (user->x_cursor >= user->current->clen + user->plen)
		return ;
	tputs(tgetstr("nd", NULL), 1, tputs_char);
	user->x_cursor++;
}

void		key_left(t_entry *user)
{
	if (user->x_cursor <= user->plen)
		return ;
	tputs(tgetstr("le", NULL), 1, tputs_char);
	user->x_cursor--;
}

void		key_up(t_entry *user)
{
	if (user->current->next)
	{
		user->current = user->current->next;
		put_cmd(user);
		user->x_cursor = user->plen + user->current->clen;
	}
}

void		key_down(t_entry *user)
{
	if (user->current->prev)
	{
		user->current = user->current->prev;
		put_cmd(user);
		user->x_cursor = user->plen + user->current->clen;
	}
}
