/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:43:26 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/17 18:22:15 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "42sh.h"

/*
** Print the env var
*/
void		ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

/*
** Copy environ
*/
char		**ft_cp_env(char **environ)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	env = NULL;
	while (environ && environ[i] != '\0')
		i++;
	if ((env = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	env[i] = '\0';
	j = 0;
	while (j < i)
	{
		env[j] = ft_strdup(environ[j]);
		j++;
	}
	return (env);
}

/*
** Destroy the copy of the environ extern var
*/
void	destroy_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	env = NULL;
}

