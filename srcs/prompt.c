/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/02 12:51:16 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/13 16:01:32 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			put_prompt(void)
{
	ft_putstr("\033[1;30m42sh\033[0m \033[1;32mλ \033[0m");
	return (7);
}
