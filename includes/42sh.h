/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:52:40 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/24 02:38:08 by jvincent         ###   ########.fr       */
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
void	ft_print_env(char **env);
char	**ft_cp_env(char **env);
void	ft_destroy_env(char **env);
char	**ft_get_env(char **env, char *var);
char	*ft_get_env_val(char **env, char *var);
char	**ft_set_env(char **env, char *key, char *value);
char	**ft_unset_env(char **env, char *key);

#endif /* !FTSH_H */

