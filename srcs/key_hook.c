/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/02 14:18:55 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/25 17:41:54 by jibanez          ###   ########.fr       */
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
	i = 0;
	while (user->current->cmd[i] != '\0')
		i++;
	while (i > user->current->clen)
	{
		user->current->cmd[i] = user->current->cmd[i - 1];
		i--;
	}
	user->current->cmd[user->x_cursor - user->plen] = key;
	user->current->clen++;
	user->x_cursor++;
	put_cmd(user);
}
