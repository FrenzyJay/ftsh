/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 14:05:14 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/24 20:33:58 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include <sys/types.h>

typedef struct			s_process
{
	pid_t				pid;
	char				**argv;
	char				state;
	char				completed;
	char				stopped;
	struct s_process	*next;
}						t_process;

typedef struct		s_job
{
	int				num;
	char			recent;
	t_process		*first_process;
	pid_t			pgid;
	char			*command;
	struct s_job	*next;
/*	char			notified;
	struct termios	tmodes;
	int				stdin;
	int				stdout;
	int				stderr;*/
}					t_job;

void	ft_viewlist_process(t_process *list);
void	ft_add_process(t_process **list, pid_t pid, char **argv);

/*
** SIGNALS
*/

void	ft_sig_handler(int c);

#endif /* LST_H */
