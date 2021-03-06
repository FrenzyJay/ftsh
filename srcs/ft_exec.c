/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:12 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/27 20:11:22 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftsh.h"

int		ft_exec_pipeline(t_node *curs, t_shenv **env);

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

int		ft_identify_path(char **arg, char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (arg && arg[0] && arg[0][i])
	{
		if (arg[0][i] == '/')
		{
			if (access(arg[0], X_OK) != -1)
				return (0);
			return (1);
		}
		i++;
	}
	if ((path = ft_get_path(arg[0], env)) == NULL)
		return (1);
	free(arg[0]);
	arg[0] = path;
	return (0);
}

void	ft_process(char **arg, t_shenv **env, int towait)
{
	pid_t	father;

	if (towait)
		father = fork();
	else
		father = 0;
	if (!father)
	{
		signals_switch();
		execve(arg[0], arg, (*env)->env);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (towait)
			wait(&((*env)->estatus));
		ft_destroy_tab(arg);
	}
}

int		ft_exec_cmd(t_node *curs, t_shenv **env, int towait)
{
	char	**arg;

	if ((arg = ft_concat_expr(curs)) == NULL)
		return (1);
	if (ft_is_builtin(arg, env))
		return (0);
	if (ft_identify_path(arg, (*env)->env))
	{
		ft_error("command not found", arg[0]);
		(*env)->estatus = 1;
		return (126);
	}
	ft_process(arg, env, towait);
	return (0);
}

int		ft_pipe_recurs(t_node *curs, t_shenv **env)
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
		exit(1);
	}
	else
	{
		close(tube[1]);
		dup2(tube[0], 0);
		close(tube[0]);
		ft_exec_cmd(curs->right, env, 0);
		exit(1);
	}
}

int		ft_exec_pipeline(t_node *curs, t_shenv **env)
{
	if (curs)
	{
		(*env)->indexpipe++;
		if (curs->token == tok_pipe)
			return (ft_pipe_recurs(curs, env));
		else if (curs->token == tok_expr)
			return (ft_exec_cmd(curs, env, 0));
	}
	return (0);
}

t_node	*ft_to_end(t_node *ast)
{
	t_node	*curs;

	curs = ast;
	while (curs)
	{
		if (curs->token == tok_end)
			return (curs);
		curs = curs->left;
	}
	return (NULL);
}

t_node	*ft_to_next_sep_and(t_node *ast)
{
	t_node	*curs;

	curs = ast;
	while (curs)
	{
		if (curs->token == tok_end || curs->token == tok_or)
			return (curs);
		curs = curs->left;
	}
	return (NULL);
}

t_node	*ft_to_next_sep_or(t_node *ast)
{
	t_node	*curs;

	curs = ast;
	while (curs)
	{
		if (curs->token == tok_end || curs->token == tok_and)
			return (curs);
		curs = curs->left;
	}
	return (NULL);
}

void	process_cmd(t_node *ast, t_shenv **env)
{
	int	father;

	if (!ast)
		return ;
	if (ast->token == tok_end || ast->token == tok_pipe)
		(*env)->estatus = 0;
	if (ast->token == tok_expr)
		ft_exec_cmd(ast, env, 1);
	else if (ast->token == tok_pipe)
	{
		(*env)->indexpipe = 0;
		father = fork();
		if (!father)
			ft_exec_pipeline(ast, env);
		else
			wait(NULL);
	}
	if (ast->token == tok_pipe)
		process_cmd(ft_to_end(ast), env);
	else if (ast->token == tok_and && (*env)->estatus == 1)
		process_cmd(ft_to_next_sep_and(ast), env);
	else if (ast->token == tok_or && (*env)->estatus == 0)
		process_cmd(ft_to_next_sep_or(ast), env);
	else
		process_cmd(ast->left, env);
}

