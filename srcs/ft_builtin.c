/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 20:59:38 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 20:13:18 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ftsh.h"

void	ft_exit(char **arg)
{
	(void)arg;
	exit(0);
}

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

char	**ft_cd(char **args, char **env)
{
	int		i;
	char	*home;
	char	*oldpwd;

	home = ft_strdup("HOME");
	oldpwd = ft_strdup("OLDPWD");
	if (args[1] == '\0')
		i = chdir(ft_get_env_val(env, home));
	else if (ft_strlen(args[1]) == 1 && args[1][0] == '-')
	{
		ft_putendl(ft_get_env_val(env, oldpwd));
		i = chdir(ft_get_env_val(env, oldpwd));
	}
	else
	{
		if ((i = ft_permissions_cd(args, &home, &oldpwd)) == 1)
			return (env);
	}
	if (i < 0)
		ft_putstr("not a dir\n");
	else
		env = update_pwd(env);
	free(home);
	free(oldpwd);
	return (env);
}

int		ft_is_builtin(char **arg, t_shenv **env)
{
	if (!arg)
		return (1);
	if (!ft_strequ(arg[0], "exit"))
		ft_exit(arg);
	else if (!ft_strequ(arg[0], "cd"))
		(*env)->env = ft_cd(arg, (*env)->env);
	else if (!ft_strequ(arg[0], "env"))
		ft_print_env((*env)->env);
	else if (!ft_strequ(arg[0], "setenv"))
		(*env)->env = ft_built_set_env(arg, (*env)->env);
	else if (!ft_strequ(arg[0], "unsetenv"))
		(*env)->env = ft_built_unset_env(arg, (*env)->env);
	else
		return (0);
	return (1);
}
