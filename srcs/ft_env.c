/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:43:26 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/20 09:22:28 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "42sh.h"

/*
** Print the env var
*/
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

/*
** Copy environ
*/
char   	**ft_cp_env(char **genv)
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

/*
** Destroy the copy of the environ extern var
*/
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

/*
** Get a var of the env
*/
char	**ft_get_env(char **env, char *var)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (var != NULL)
		size = ft_strlen(var);
	var[size] = '=';
	while (env && env[i] && ft_strncmp(env[i], var, size) != 0)
		i++;
	var[size] = '\0';
	if (env && env[i])
		return (&(env[i]));
	return (NULL);
}

char	**ft_add_env(char **env, char *key, char *value)
{
	int		i;
	int		j;
	char	*tofree;
	char	**new;

	i = 0;
	j = 0;
	new = NULL;
	while (env && env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	while (j < i)
	{
		new[j] = ft_strdup(env[j]);
		j++;
	}
	new[j] = ft_strjoin(key, "=");
	tofree = new[j];
	new[j] = ft_strjoin(new[j], value);
	free(tofree);
	new[j + 1] = NULL;
	ft_destroy_env(env);
	return (new);
}

/*
** Set or update a var in the env
*/
char	**ft_set_env(char **env, char *key, char *value)
{
	char	**temp;
	char	*var;
	char	**new;

	new = NULL;
	temp = NULL;
	if ((temp = ft_get_env(env, key)) == NULL)
		new = ft_add_env(env, key, value);
	else
	{
		free(*temp);
		var = ft_strjoin(key, "=");
		*temp = ft_strjoin(var, value);
		free(var);
		new = env;
	}
	return (new);
}