/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_travel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 17:46:09 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 19:16:04 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <string.h>
#include <readline.h>

void		key_end(t_entry *user)
{
	int		i;

	i = user->cursor;
	while (user->current->cmd[i] != '\0')
	{
		move_right(user);
		user->cursor++;
		i++;
	}
}

void		key_home(t_entry *user)
{
	int		i;

	i = user->cursor;
	while (i > 0)
	{
		move_left(user);
		user->cursor--;
		i--;
	}
}

void		key_next_word(t_entry *user)
{
	int		i;

	i = user->cursor;
	while (user->current->cmd[i] != ' ' && i < user->current->clen)
	{
		i++;
		move_right(user);
		user->cursor++;
	}
	while (user->current->cmd[i] == ' ' && i < user->current->clen)
	{
		i++;
		move_right(user);
		user->cursor++;
	}
}

void		key_prev_word(t_entry *user)
{
	int		i;

	i = user->cursor;
	while (user->current->cmd[i - 1] == ' ' && i > 0)
	{
		i--;
		move_left(user);
		user->cursor--;
	}
	while (user->current->cmd[i - 1] != ' ' && i > 0)
	{
		i--;
		move_left(user);
		user->cursor--;
	}
}
