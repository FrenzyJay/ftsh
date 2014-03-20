/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/20 09:19:27 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "42sh.h"

void	sh_init(char ***env)
{
	*env = ft_cp_env(environ);
}

int main(int argc, char **argv)
{
	char	**env;
	char	*var;

	env = NULL;
	if (argc > 1)
		return (ft_error(argv[0]));
	ft_putendl("~~ Hum ಠ_ಠ ~~\n");
	sh_init(&env);

//	exec_cmd(NULL);
	var = ft_strdup("NEW");
	env = ft_set_env(env, var, "new home");
	free(var);
	ft_print_env(env);

	ft_destroy_env(env);
	pause();
	return (0);
}

