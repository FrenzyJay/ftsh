/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:52:40 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 20:13:44 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSH_H
# define FTSH_H

# include "libft.h"
# include "job.h"
# include "parser.h"
# include "readline.h"

extern char		**environ;

typedef struct	s_shenv
{
	char		**env;
	int			estatus;
	int			indexpipe;
}				t_shenv;

/*
** MAIN
*/
t_job			*singleton(void);

/*
** FT_INIT.C
*/
t_shenv			*sh_init();
void			sh_desinit(t_shenv **env);

/*
** FT_EXEC.C
*/
void			process_cmd(t_node *ast, t_shenv **env);

/*
** FT_ENV.C
*/
void			ft_print_env(char **env);
char			**ft_cp_env(char **env);
void			ft_destroy_env(char **env);
char			**ft_get_env(char **env, char *var);
char			*ft_get_env_val(char **env, char *var);
char			**ft_set_env(char **env, char *key, char *value);
char			**ft_unset_env(char **env, char *key);
int				ft_permissions_cd(char **args, char **home, char **oldpwd);

/*
** FT_SIGNALS.C
*/
void			signals_inhibit();
void			signals_switch();

/*
** FT_BUILTIN.C
*/
int				ft_is_builtin(char **arg, t_shenv **env);
char			**update_pwd(char **env);
void			ft_exit(char **arg);
char			**ft_built_set_env(char **arg, char **env);
char			**ft_built_unset_env(char **arg, char **env);
char			**ft_cd(char **args, char **env);

#endif

