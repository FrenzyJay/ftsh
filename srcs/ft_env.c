/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:43:26 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 20:08:42 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftsh.h"

/*
** Add something to the env
*/
char		**ft_add_env(char **env, char *key, char *value)
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
	if ((new = (char **)malloc(sizeof(char *) * (i + 2))) == NULL)
		return (NULL);
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
char		**ft_set_env(char **env, char *key, char *value)
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

/*
** Remove something from the env
*/
static void	ft_fresh_env(char **env, char **fresh, char *var, int i)
{
	int		size;
	int		j;

	j = i - 1;
	size = ft_strlen(var);
	while (i >= 0)
	{
		if (ft_strncmp(env[i], var, size) == 0)
			i--;
		else
		{
			fresh[j] = env[i];
			i--;
			j--;
		}
	}
}

char		**ft_unset_env(char **env, char *key)
{
	char	**fresh;
	int		i;
	char	**var;

	i = 0;
	if ((var = ft_get_env(env, key)) == NULL)
		return (env);
	while (env && env[i])
		i++;
	if ((fresh = (char **)malloc(sizeof(char *) * i)) == NULL)
		return (env);
	fresh[i - 1] = '\0';
	i -= 1;
	ft_fresh_env(env, fresh, *var, i);
	free(*var);
	*var = NULL;
	free(env);
	env = NULL;
	return (fresh);
}
