/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:12 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/26 05:31:48 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "42sh.h"
#include "readline.h"

/*
** Signals switch
*/
void	signals_switch()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

/*
** En attendant le parseur d'expr :)
*/
char	**ft_concat_expr(t_node *node)
{
	t_node	*curs;
	char	**fresh;
	int		i;

	curs = node;
	i = 0;
	while (curs)
	{
		i++;
		curs = curs->right;
	}
	if ((fresh = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	curs = node;
	i = 0;
	while (curs)
	{
		fresh[i] = ft_strdup(curs->value);
		curs = curs->right;
		i++;
	}
	fresh[i] = NULL;
	return (fresh);
}

int	process_cmd(t_node *ast, t_shenv **env)
{
	t_node	*curs;
	int		father;
	char	**arg;

	curs = ast;
	while (curs)
	{
		if (curs && curs->token == tok_expr)
		{
			arg = ft_concat_expr(curs);
			default_term_mode();
			father = fork();
			if (father != 0)
			{
				wait(NULL);
				ft_destroy_env(arg);
			}
			else
			{
				signals_switch();
				execve(arg[0], arg, (*env)->env);
				ft_putendl("Gros fail");
				exit(EXIT_FAILURE);
			}
		}
		curs = curs->left;
	}
	return (0);
}

