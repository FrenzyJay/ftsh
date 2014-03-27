/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 18:12:49 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 00:05:12 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "readline.h"

static void			init_entry(t_entry *user, t_hlst *historic);
static t_hlst		*copy_historic(t_hlst *historic);
static void			add_to_historic(t_entry *user, t_hlst **historic);

/*
** Get the user entry and return it when return key is press
*/

char				*read_line(void)
{
	static t_hlst	*historic = NULL;
	t_entry			user;
	char			*buffer[4];
	unsigned int	key;

	key = 0;
	init_entry(&user, historic);
	while (key != RETURN)
	{
		ft_bzero(buffer, 4);
		read(0, buffer, 4);
		key = *(unsigned int *)buffer;
		if (key == CTRL_D)
		{/**/
			default_term_mode();
			exit(1); /* put builtin exit here */
		}/**/
		key_hook(key, &user);
	}
	add_to_historic(&user, &historic);
	ft_putchar('\n');
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
	user->x_cursor = user->plen;
	user->lines = 1;
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

/*
** Add the last used command to the historic list
*/

static void			add_to_historic(t_entry *user, t_hlst **historic)
{
	if (user->current->cmd[0] != '\0')
		hlst_push_front(historic, hlst_new(ft_strdup(user->current->cmd)));
}
