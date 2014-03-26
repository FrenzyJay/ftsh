/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/26 06:00:43 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "42sh.h"
#include "libft.h"
#include "parser.h"
#include "readline.h"

/*
** Signals inhibiter
*/
void	signals_inhibit()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

/*
** Init sequence
*/
t_shenv	*sh_init()
{
	t_shenv	*fresh;

	fresh = (t_shenv *)malloc(sizeof(t_shenv));
	if (fresh)
		fresh->env = ft_cp_env(environ);
	return (fresh);
}

/*
** Destroy env && shenv
*/
void	sh_desinit(t_shenv **env)
{
	ft_destroy_env((*env)->env);
	free(*env);
	*env = NULL;
}

/*
** SHELL CORE
*/
int		shell_core(t_shenv **env)
{
	char	*cmd;
	t_node	*ast;

	while (42)
	{
		raw_term_mode();
		cmd = read_line();
		ft_putendl(cmd);//
		if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
			break ;
		ast = ft_parser(cmd);
		ft_put_ast(ast, 0);//
		write(1, "\n", 1);

		process_cmd(ast, env);
	}
	return (0);
}

/*
** Main routine
*/
int 	main(int argc, char **argv)
{
	t_shenv	*env;

	if (argc > 1)
		return (ft_error(argv[0]));
	ft_putendl("~~ Hum ಠ_ಠ ~~ \n");
	env = sh_init();
	if (env && env->env)
	{
		signals_inhibit();
		shell_core(&env);
		sh_desinit(&env);
	}
	return (0);
}

