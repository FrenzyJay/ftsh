/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:52:40 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/17 16:52:59 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSH_H
# define FTSH_H

# include "libft.h"

extern char **environ;

/*
** FT_EXEC.C
*/
int		exec_cmd(char *cmd);

/*
** FT_ENV.C
*/
char	**ft_cp_env(char **environ);

#endif /* !FTSH_H */

