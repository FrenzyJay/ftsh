/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:12 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 07:40:47 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "42sh.h"

int		ft_exec_pipeline(t_node *curs, t_shenv **env);

/*
** Arg tab size
*/
int		ft_arg_size(t_node *node)
{
	if (!node || node->token != tok_expr)
		return (0);
	return (1 + ft_arg_size(node->right));
}

void	ft_concat_value(char **tab, t_node *node, int i)
{
	if (!node || node->token != tok_expr)
		return ;
	tab[i] = ft_strdup(node->value);
	ft_concat_value(tab, node->right, i + 1);
}

/*
** En attendant le parseur d'expr :)
*/
char	**ft_concat_expr(t_node *node)
{
	char	**fresh;
	int		i;

	i = ft_arg_size(node);
	if ((fresh = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	ft_concat_value(fresh, node, 0);
	fresh[i] = NULL;
	return (fresh);
}

/*
** Get the path of a cmd
*/
char	*ft_get_path(char *bin, char **env)
{
	char	**tpath;
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	path = ft_strdup("PATH");
	tpath = ft_strsplit(ft_get_env_val(env, path), ':');
	tmp = NULL;
	free(path);
	while (tpath && tpath[i])
	{
		path = ft_strjoin(tpath[i], "/");
		tmp = path;
		path = ft_strjoin(path, bin);
		free(tmp);
		if (access(path, X_OK) != -1)
		{
			ft_destroy_tab(tpath);
			return (path);
		}
		i++;
	}
	ft_destroy_tab(tpath);
	return (NULL);
}

/*
** Execute a solo cmd
*/
int		ft_exec_cmd(t_node *curs, t_shenv **env, int towait)
{
	char	**arg;
	pid_t	father;

	if ((arg = ft_concat_expr(curs)) == NULL)
		return (1);	
	if (ft_is_builtin(arg, env))
		return (0);
	if ((arg[0] = ft_get_path(arg[0], (*env)->env)) == NULL)
	{
		ft_putendl("Command not found");
		return (0);
	}
	if (towait)
		father = fork();
	else
		father = 0;
	if (!father)
	{
		signals_switch();
		execve(arg[0], arg, (*env)->env);
		ft_putendl("Gros fail");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (towait)
			wait(NULL);
		ft_destroy_env(arg);
	}
	return (0);
}

/*
** Process the pipeline
*/
void	ft_pipe_recurs(t_node *curs, t_shenv **env)
{
	pid_t	father;
	int		tube[2];

	pipe(tube);
	father = fork();
	if (!father)
	{
		close(tube[0]);
		dup2(tube[1], 1);
		close(tube[1]);
		ft_exec_pipeline(curs->left, env);
	}
	else
	{
		close(tube[1]);
		dup2(tube[0], 0);
		close(tube[0]);
		if (ft_exec_cmd(curs->right, env, 0) == 0)
			exit(1);
	}
}

/*
** Handle the pipeline
*/
int		ft_exec_pipeline(t_node *curs, t_shenv **env)
{
	if (curs)
	{
		if (curs->token == tok_expr)
			ft_exec_cmd(curs, env, 0);
		else if (curs->token == tok_pipe)
			ft_pipe_recurs(curs, env);
	}
	return (0);
}

/*
** Skip all the pipe and go to the next semi-colon
*/
t_node	*ft_zap_pipe(t_node *ast)
{
	t_node	*curs;

	curs = ast;
	while (curs)
	{
		if (curs->token == tok_expr)
			return (curs->left);
		curs = curs->left;
	}
	return (NULL);
}

void	process_cmd(t_node *ast, t_shenv **env)
{
	int	father;

	if (!ast)
		return ;
	if (ast->token == tok_expr)
	{
		if (ft_exec_cmd(ast, env, 1))
			ft_putendl("wtf");
	}
	else if (ast->token == tok_pipe)
	{
		father = fork();
		if (!father)
			ft_exec_pipeline(ast, env);
		else
			wait(NULL);
		ast = ft_zap_pipe(ast);
	}
	process_cmd(ast->left, env);
}

