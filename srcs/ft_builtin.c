/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 20:59:38 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/24 03:36:04 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** Update the PWD and OLDPWD
*/
char	**update_pwd(char **env)
{
	char	*buffer;
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD");
	oldpwd = ft_strdup("OLDPWD");
	env = ft_set_env(env, oldpwd, ft_get_env_val(env, pwd));
	buffer = getcwd(NULL, 0);
	env = ft_set_env(env, pwd, buffer);
	free(pwd);
	free(oldpwd);
	return (env);
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
		env = update_pwd(env);
	return (env);
}

