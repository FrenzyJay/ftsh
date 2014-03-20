/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:20 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/17 18:26:09 by jvincent         ###   ########.fr       */
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
	var = ft_strdup("HOME");
	ft_putstr(ft_get_env(env, var));

	free(var);
	ft_destroy_env(env);
	pause();
	return (0);
}

