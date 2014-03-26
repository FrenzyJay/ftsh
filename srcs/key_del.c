/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 17:12:11 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/26 19:15:50 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <string.h>
#include "readline.h"

/*
** Delete the character on the left side of the cursor pos
** Move cursor to the left
*/

void				key_backspace(t_entry *user)
{
	int				i;

	if (user->cursor <= 0)
		return ;
	i = user->cursor - 1;
	while (user->current->cmd[i] != '\0')
	{
		user->current->cmd[i] = user->current->cmd[i + 1];
		i++;
	}
	user->current->clen--;
	user->cursor--;
	put_cmd(user);
}

/*
** Delete the character on the cursor pos
** Don't move cursor
*/

void				key_delete(t_entry *user)
{
	int				i;

	i = user->cursor;
	while (user->current->cmd[i] != '\0')
	{
		user->current->cmd[i] = user->current->cmd[i + 1];
		i++;
	}
	user->current->clen--;
	put_cmd(user);
}
