/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 05:43:59 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "42sh.h"
#include "get_next_line.h"
#include "readline.h"

/*
** Main routine
*/

int		main(int argc, char **argv)
{
	char	*entry;
	char	*error;
	t_node	*ast;

	while (get_next_line(0, &entry))
	{
		ast = ft_parser(entry);
		if ((error = ft_parser_check_error(ast)))
			ft_printf("ftsh: parse error near '%s'\n", error);
		else
			ft_put_ast(ast);
		ft_ast_destroy(&ast);
	}

	return (0);
	(void)argc;
	(void)argv;
}

