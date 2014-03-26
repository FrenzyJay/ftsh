/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_buff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 18:02:18 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/25 17:40:58 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "readline.h"

char			*dynbuff(char *buff, int len, int add)
{
	char		*new;

	new = ft_strnew(len + add);
	ft_strncpy(new, buff, len);
	ft_strdel(&buff);
	return (new);
}
