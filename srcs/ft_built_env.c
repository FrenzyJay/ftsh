/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 17:49:40 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 20:13:59 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftsh.h"

/*
** Built-in UNSET-ENV
*/
char	**ft_built_unset_env(char **arg, char **env)
{
	int		i;

	i = 1;
	while (arg[i] != NULL)
	{
		env = ft_unset_env(env, arg[i]);
		i++;
	}
	return (env);
}

/*
** Built-in SET-ENV
*/
char	**ft_built_set_env(char **arg, char **env)
{
	char	*var;

	var = (char *)malloc(1);
	var[0] = 0;
	if (arg[1] == NULL)
		ft_print_env(env);
	else if (arg[2] == NULL)
		env = ft_set_env(env, arg[1], var);
	else if (arg[3] == NULL)
		env = ft_set_env(env, arg[1], arg[2]);
	else
		ft_putendl("setenv : Too many arguments.");
	return (env);
}
