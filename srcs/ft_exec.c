/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:12 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/17 18:37:44 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

int	exec_cmd(char *comd)
{
	char	*cmd = "/bin/ls";
	char	*arg[] = {"ls", "-l", NULL};
	int		father;
	char	buf[10];
	int		ret;

	(void)comd;
	father = fork();
	if (father != 0)
	{
		wait(NULL);
		while ((ret = read(0, buf, 10)) > 0)
			write(1, buf, ret);
	}
	else
		execve(cmd, arg, NULL);
	return (0);
}

