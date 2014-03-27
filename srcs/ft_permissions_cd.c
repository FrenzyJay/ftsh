/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_permissions_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapillo <llapillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 15:21:20 by llapillo          #+#    #+#             */
/*   Updated: 2014/03/27 20:15:50 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftsh.h"

int		ft_permissions_cd(char **args, char **home, char **oldpwd)
{
	if (access(args[1], F_OK) == -1)
	{
		ft_putstr("no such file\n");
		free(*home);
		free(*oldpwd);
		return (1);
	}
	if (access(args[1], X_OK) == -1)
	{
		ft_putstr("permission denied\n");
		free(*home);
		free(*oldpwd);
		return (1);
	}
	return (chdir(args[1]));
}
