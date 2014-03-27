/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 20:59:38 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 05:45:52 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "42sh.h"

/*
** Built-in SET-ENV
*/
char	**ft_built_set_env(char **arg, char **env)
{
	(void)arg;
	(void)env;
	return (env);
}

/*
** Built-in EXIT
*/
void	ft_exit(char **arg)
{
	(void)arg;
	exit(0);
}

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
		if (access(args[1], F_OK) == -1)
		{
/*			ft_printf("no such directory : %s\n", args[1]);*/
			ft_putstr("no such file\n");
			free(home);
			free(oldpwd);
			return (env);
		}
		if (access(args[1], X_OK) == -1)
		{
/*			ft_printf("Permission denied : %s\n", args[1]);*/
			ft_putstr("permission denied\n");
			free(home);
			free(oldpwd);
			return (env);
		}
		i = chdir(args[1]);
	}
	if (i < 0)
	{
/*		ft_printf("not a directory : %s\n", args[1]);*/
		ft_putstr("not a dir\n");
	}
	else
		env = update_pwd(env);
	free(home);
	free(oldpwd);
	return (env);
}

/*
** Test and launch builtin
*/
int		ft_is_builtin(char **arg, t_shenv **env)
{
	int	i;

	if (!arg)
		return (1);
	i = ft_strlen(arg[0]);
	if (!ft_strncmp(arg[0], "exit", i))
		ft_exit(arg);
	else if (!ft_strncmp(arg[0], "cd", i))
		(*env)->env = ft_cd(arg, (*env)->env);
	else if (!ft_strncmp(arg[0], "env", i))
		ft_print_env((*env)->env);
	else if (!ft_strncmp(arg[0], "setenv", i))
		(*env)->env = ft_built_set_env(arg, (*env)->env);
	else
		return (0);
	return (1);
}

