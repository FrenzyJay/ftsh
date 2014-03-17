/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:43:26 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/17 16:54:35 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "42sh.h"

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

