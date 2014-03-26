/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 14:39:35 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/26 19:33:57 by llapillo         ###   ########.fr       */
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
#include <stdlib.h>

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
		execve("/bin/sleep", cmd, env);
}

t_job	*singleton(void)
{
	static t_job	*lst = NULL;

	return (lst);
}

int		main(int ac, char **av, char **env)
{
//	t_process	*lst;
//	pid_t		ft;
//	char		*buf;
//	char		*cmd[3];
	t_job		*lstj;
	pid_t		*tab_p;

	tab_p = (pid_t *)malloc(sizeof(pid_t) * 3);
	lstj = singleton();
	tab_p[0] = 1000;
	tab_p[1] = 1001;
	tab_p[2] = 1002;
	ft_add_job(&lstj, tab_p, 3,  "lol i | dont know what | i do");
	tab_p[0] = 2000;
//	tab_p[1] = 2001;
//	tab_p[2] = 2002;
	ft_add_job(&lstj, tab_p, 1,  "lol i dont know what i do");
	tab_p[0] = 3000;
	tab_p[1] = 3001;
	tab_p[2] = 3002;
	ft_add_job(&lstj, tab_p, 3,  "lol i | dont know what | i do");
	tab_p[0] = 4000;
	tab_p[1] = 4001;
	tab_p[2] = 4002;
	ft_add_job(&lstj, tab_p, 3,  "lol i | dont know what | i do");
	tab_p[0] = 5000;
	tab_p[1] = 5001;
	tab_p[2] = 5002;
	ft_add_job(&lstj, tab_p, 3,  "lol i | dont know what | i do");
	tab_p[0] = 6000;
	tab_p[1] = 6001;
	tab_p[2] = 6002;
	ft_add_job(&lstj, tab_p, 3,  "lol i | dont know what | i do");
	tab_p[0] = 7000;
	tab_p[1] = 7001;
	tab_p[2] = 7002;
	ft_add_job(&lstj, tab_p, 3,  "lol i | dont know what | i do");
	tab_p[0] = 8000;
	tab_p[1] = 8001;
//	tab_p[2] = 8002;
	ft_add_job(&lstj, tab_p, 2,  "lol i dont know | what i do");
	tab_p[0] = 9000;
//	tab_p[1] = 9001;
//	tab_p[2] = 9002;
	ft_add_job(&lstj, tab_p, 1,  "lol i dont know what i do");
	tab_p[0] = 1110;
	tab_p[1] = 1111;
	tab_p[2] = 1112;
	ft_add_job(&lstj, tab_p, 3,  "lol i | dont know what | i do");
	ft_viewlist_job(lstj);
//	(void)lstj;
	(void)env;
	(void)av;
	(void)ac;
//	cmd[0] = "sleep";
//	cmd[1] = "2";
//	cmd[2] = 0;
//	if (ac == 1)
//		return (1);
	if (signal(SIGCHLD, ft_sig_handler) == SIG_ERR)
		ft_putendl("can't catch SIGCHLD");
//	if (signal(SIGINT, ft_sig_handler) == SIG_ERR)
//		ft_putendl("can't catch SIGINT");
	if (signal(SIGTSTP, ft_sig_handler) == SIG_ERR)
		ft_putendl("can't catch SIGTSTP");
//	lst = NULL;
//	ft = 50000;
//	ft_putnbr(getpgid(51749));
//	ft_putchar('\n');
//	ft_exec(&lst, cmd, env);
//	ft_add_process(&lst, ft, cmd);
//	ft_viewlist_process(lst);
//	buf = NULL;
//	while (42)
//	{
		//read(0, buf, 1);
		//if (strcmp(buf, "e"))
		//	break ;
//		pause();
//	}
	return (0);
}
