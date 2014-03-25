/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/25 21:26:25 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "42sh.h"
#include "parser.h"
#include "readline.h"

void	sh_init(char ***env)
{
	*env = ft_cp_env(environ);
}

/*
** Main routine
*/
int main(int argc, char **argv)
{
	char	**env;
	char	*cmd;
	t_node	*ast;

	env = NULL;
	if (argc > 1)
		return (ft_error(argv[0]));
	ft_putendl("~~ Hum ಠ_ಠ ~~ \n");
	sh_init(&env);
	while (42)
	{
		raw_term_mode();
		cmd = read_line();
		ft_putendl(cmd);
		ast = ft_parser(cmd);
		ast = ft_ast_rewind(ast);
		ft_put_ast(ast, 0);
		write(1, "\n", 1);
	}
	ft_destroy_env(env);
	return (0);
}

