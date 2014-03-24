/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 14:39:35 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/24 20:41:58 by llapillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>

/* Just a comment :) */

void	ft_exec(t_process **lst, char **cmd, char **env)
{
	pid_t	ft;

	ft = fork();
	if (ft != 0)
	{
		ft_add_process(lst, ft, cmd);
		wait(&ft);
	}
	else
		execve("/usr/bin/emacs", cmd, env);
}

int		main(int ac, char **av, char **env)
{
	t_process	*lst;
//	pid_t		ft;
//	char		*buf;
	char		*cmd[3];

	(void)av;
	(void)ac;
	cmd[0] = "emacs";
//	cmd[1] = "-R";
//	cmd[2] = "/";
//	if (ac == 1)
//		return (1);
	if (signal(SIGINT, ft_sig_handler) == SIG_ERR)
		ft_putendl("can't catch SIGINT");
	if (signal(SIGTSTP, ft_sig_handler) == SIG_ERR)
		ft_putendl("can't catch SIGTSTP");
	lst = NULL;
//	ft = 50000;
//	ft_putnbr(getpgid(51749));
//	ft_putchar('\n');
	ft_exec(&lst, cmd, env);
//	ft_add_process(&lst, ft, cmd);
	ft_viewlist_process(lst);
//	buf = NULL;
	while (42)
	{
		//read(0, buf, 1);
		//if (strcmp(buf, "e"))
		//	break ;
		pause();
	}
	return (0);
}
