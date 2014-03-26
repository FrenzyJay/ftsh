/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/02 14:18:55 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/26 20:31:28 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include "libft.h"
#include "readline.h"

static void			add_char(unsigned int key, t_entry *user);

/*
** Call the right func and print ascii characters
*/

static void			exe_key(t_entry *user, void (*f)(t_entry *))
{
	f(user);
}

void				key_hook(unsigned int key, t_entry *user)
{
	int					i;
	static t_key_func	func_tab[] =
	{
		{RIGHT, &key_right},
		{LEFT, &key_left},
		{UP, &key_up},
		{DOWN, &key_down},
		{BACKSPACE, &key_backspace},
		{DELETE, &key_delete},
		{END, &key_end},
		{HOME, &key_home},
		{CTRL_E, &key_end},
		{CTRL_A, &key_home},
		{CTRL_B, &key_prev_word},
		{CTRL_N, &key_next_word},
		{0, NULL}
	};

	i = 0;
	while (func_tab[i].f != NULL)
	{
		if (func_tab[i].key == key)
			exe_key(user, func_tab[i].f);
		i++;
	}
	if (ft_isprint(key))
		add_char(key, user);
}

/*
** Add one characther to the user command at the cursor position
*/

static void			add_char(unsigned int key, t_entry *user)
{
	int				i;

	user->current->cmd = dynbuff(user->current->cmd, user->current->clen, 1);
	i = user->current->clen;
	while (i > user->cursor)
	{
		user->current->cmd[i] = user->current->cmd[i - 1];
		i--;
	}
	user->current->cmd[user->cursor] = key;
	user->current->clen++;
	user->cursor++;
	move_right(user);
	put_cmd(user);
}
