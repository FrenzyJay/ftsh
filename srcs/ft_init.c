/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:52:23 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 17:32:41 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "42sh.h"

/*
** Init sequence
*/
t_shenv	*sh_init()
{
	t_shenv	*fresh;

	fresh = (t_shenv *)malloc(sizeof(t_shenv));
	if (fresh)
		fresh->env = ft_cp_env(environ);
	fresh->estatus = 0;
	fresh->indexpipe = 0;
	return (fresh);
}

/*
** Destroy env && shenv
*/
void	sh_desinit(t_shenv **env)
{
	ft_destroy_env((*env)->env);
	free(*env);
	*env = NULL;
}

