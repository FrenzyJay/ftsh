/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 19:25:51 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "ftsh.h"

/*
** SINGLETON
*/
t_job		*singleton(void)
{
	static t_job	*jobs = NULL;

	return (jobs);
}


/*
** SHELL CORE
*/
static int	shell_core(t_shenv **env)
{
	char	*cmd;
	t_node	*ast;

	while (42)
	{
		cmd = read_line();
		ast = ft_parser(cmd);
		if (ast)
			process_cmd(ast, env);
		ft_ast_destroy(&ast);
	}
	return (0);
}

/*
** Main routine
*/
int			main(int argc, char **argv)
{
	t_shenv	*env;

	(void)argc;
	(void)argv;
	ft_putendl("~~ Hum ಠ_ಠ ~~ \n");
	env = sh_init();
	if (env && env->env)
	{
		signals_inhibit();
		shell_core(&env);
		sh_desinit(&env);
		signals_switch();
	}
	return (0);
}

