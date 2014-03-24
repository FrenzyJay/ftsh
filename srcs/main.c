/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/24 06:08:32 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "42sh.h"

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
	char	*var;

	env = NULL;
	if (argc > 1)
		return (ft_error(argv[0]));
	ft_putendl("~~ Hum ಠ_ಠ ~~\n");
	sh_init(&env);

	var = ft_strdup("HOME");

//	printf("\n\n%s\n\n", ft_get_env_val(env, var));

	env = ft_set_env(env, var, "more crap");

	ft_print_env(env);

//	printf("\n\n%s\n\n", ft_get_env_val(env, var));

	free(var);
	ft_destroy_env(env);
	return (0);
}

