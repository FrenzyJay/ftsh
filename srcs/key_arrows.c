/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_arrows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 13:50:26 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 16:25:46 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <stdlib.h>
#include "libft.h"
#include "readline.h"

void		key_right(t_entry *user)
{
	if (user->cursor >= user->current->clen)
		return ;
	move_right(user);
	user->cursor++;
}

void		key_left(t_entry *user)
{
	if (user->cursor <= 0)
		return ;
	move_left(user);
	user->cursor--;
}

void		key_up(t_entry *user)
{
	if (user->current->next)
	{
		user->current = user->current->next;
		user->cursor = user->current->clen;
		put_cmd(user);
	}
}

void		key_down(t_entry *user)
{
	if (user->current->prev)
	{
		user->current = user->current->prev;
		user->cursor = user->current->clen;
		put_cmd(user);
	}
}
