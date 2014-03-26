/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_travel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 17:46:09 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/25 17:42:03 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <string.h>
#include <readline.h>

/*
** Move the cursor to the end of the current command line
*/

void		key_end(t_entry *user)
{
	int		i;

	i = 0;
	while (user->current->cmd[i] != '\0')
		i++;
	user->x_cursor = i + user->plen;
	tputs(tgoto(tgetstr("ch", NULL), 0, user->x_cursor), 1, tputs_char);
}

/*
** Move the cursor to the begining of the current command line
*/

void		key_home(t_entry *user)
{
	user->x_cursor = user->plen;
	tputs(tgoto(tgetstr("ch", NULL), 0, user->x_cursor), 1, tputs_char);
}

/*
** Move the cursor to the next word on the current command line
*/

void		key_next_word(t_entry *user)
{
	int		i;

	i = user->x_cursor - user->plen;
	while (user->current->cmd[i] != ' ' && user->current->cmd[i] != '\0')
		i++;
	while (user->current->cmd[i] == ' ')
		i++;
	user->x_cursor = i + user->plen;
	tputs(tgoto(tgetstr("ch", NULL), 0, user->x_cursor), 1, tputs_char);
}

/*
** Move the cursor to the previous word on the current command line
*/

void		key_prev_word(t_entry *user)
{
	int		i;

	i = user->x_cursor - user->plen;
	while (user->current->cmd[i - 1] == ' ')
		i--;
	while (user->current->cmd[i - 1] != ' ' && i > 0)
		i--;
	user->x_cursor = i + user->plen;
	tputs(tgoto(tgetstr("ch", NULL), 0, user->x_cursor), 1, tputs_char);
}
