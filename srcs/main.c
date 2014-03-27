/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 01:44:50 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "42sh.h"
#include "libft.h"
#include "parser.h"
#include "readline.h"

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
		if (cmd && *cmd && ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
			break ;
		ast = ft_parser(cmd);
		default_term_mode();
		if (ast)
			process_cmd(ast, env);
		ft_ast_destroy(&ast);
	}
	return (0);
}

/*
** Main routine
*/
int 	main(int argc, char **argv)
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
	}
	return (0);
	(void)argc;
	(void)argv;
}

