/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 16:50:37 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 20:14:40 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

char	**ft_cp_env(char **genv)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	env = NULL;
	while (genv && genv[i] != '\0')
		i++;
	if ((env = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	env[i] = '\0';
	j = 0;
	while (genv && j < i)
	{
		env[j] = ft_strdup(genv[j]);
		j++;
	}
	return (env);
}

void	ft_destroy_env(char **env)
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

char	**ft_get_env(char **env, char *var)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (var != NULL)
	{
		size = ft_strlen(var);
		var[size] = '=';
		while (env && env[i] && ft_strncmp(env[i], var, (size + 1)) != 0)
			i++;
		var[size] = '\0';
		if (env && env[i])
			return (env + i);
	}
	return (NULL);
}

char	*ft_get_env_val(char **env, char *var)
{
	int		i;
	char	**tmp;
	char	*fck;

	i = 0;
	if (var && env)
	{
		if ((tmp = ft_get_env(env, var)) == NULL)
			return (NULL);
		fck = *tmp;
		while (fck && fck[i] && fck[i] != '=')
			i++;
		if (tmp && *tmp)
			return (&fck[i + 1]);
	}
	return (NULL);
}
