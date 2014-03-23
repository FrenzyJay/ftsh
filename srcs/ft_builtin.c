/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 20:59:38 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/23 22:59:08 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** Update the PWD and OLDPWD
*/
void	update_pwd(char **env)
{
	int		i;
	char	*pathtmp;
	char	*buffer;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
		{
			pathtmp = ft_strchr(env[i], '=');
			buffer = getcwd(NULL, 0);
			env[i] = ft_strjoin("PWD=", buffer);
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD", 6) == 0)
		{
			env[i] = ft_strjoin("OLDPWD=", pathtmp);
		}
		i++;
	}
}

/*
** Cmd "cd" : change the current directory
*/
char	**ft_cd(char **args, char **env)
{
	int		i;

	if (args[1] == '\0')
		i = chdir(ft_get_var(env, "HOME"));		
	else if (ft_strlen(args[1]) == 1 && args[1][0] == '-')
		i = chdir(ft_get_var(env, "OLDPWD"));
	else
	{
		if (access(args[1], F_OK) == -1)
		{
			ft_printf("no such directory : %s\n", args[1]);
			return (env);
		}
		if (access(args[1], X_OK) == -1)
		{
			ft_printf("Permission denied : %s\n", args[1]);
			return (env);
		}
		i = chdir(args[1]);
	}
	if (i < 0)
		ft_printf("not a directory : %s\n", args[1]);
	else
		update_pwd(env);
	return (env);
}

