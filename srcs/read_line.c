/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 18:12:49 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 18:31:10 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "readline.h"

static void			init_entry(t_entry *user, t_hlst *historic);
static t_hlst		*copy_historic(t_hlst *historic);
static void			exit_ftsh(void);

/*
** Get the user entry and return it when return key is press
*/

char				*read_line(void)
{
	static t_hlst	*historic = NULL;
	t_entry			user;
	char			*buffer[4];
	unsigned int	key;

	raw_term_mode();
	tputs(tgetstr("sc", NULL), 1, tputs_char);
	key = 0;
	init_entry(&user, historic);
	while (key != RETURN)
	{
		ft_bzero(buffer, 4);
		read(0, buffer, 4);
		key = *(unsigned int *)buffer;
		if (key == CTRL_D)
			exit_ftsh();
		key_hook(key, &user);
	}
	if (user.current->cmd[0] != '\0')
		hlst_push_front(&historic, hlst_new(ft_strdup(user.current->cmd)));
	while (user.current->prev)
		user.current = user.current->prev;
	ft_destroy_hlst(user.current);
	ft_putchar('\n');
	default_term_mode();
	return (user.current->cmd);
}


/*
** Init the t_entry struct and put the prompt
*/

static void			init_entry(t_entry *user, t_hlst *historic)
{
	user->current = copy_historic(historic);
	hlst_push_front(&(user->current), hlst_new(ft_strnew(RADIX)));
	user->plen = put_prompt();
	user->cursor = 0;
}

/*
** Copy the historic t_hlst
*/

static t_hlst		*copy_historic(t_hlst *historic)
{
	t_hlst			*new;

	new = NULL;
	while (historic)
	{
		hlst_push_back(&new, hlst_new(ft_strdup(historic->cmd)));
		historic = historic->next;
	}
	return (new);
}

static void			exit_ftsh(void)
{
	write(1, "\n", 1);
	default_term_mode();
	exit(0);
}
