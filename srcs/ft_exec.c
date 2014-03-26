/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:39:12 by jvincent          #+#    #+#             */
/*   Updated: 2014/03/26 18:12:27 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "42sh.h"
#include "readline.h"

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
	if (!node)
		return ;
	tab[i] = ft_strdup(node->value);
	ft_concat_value(tab, node->right, i + 1);
}

void	putsplit(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    {
      ft_putendl(tab[i]);
      i++;
      }
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

int		exec_cmd(t_node *curs, t_shenv **env)
{
	char	**arg;
	int		father;

	ft_putendl("--DEBUT D EXEC DE COMMANDE / exec_cmd");

  printf("---- AVANT CONCAT ----------------------------------------------------------------------------------- %p -------------\n", curs);


	if ((arg = ft_concat_expr(curs)) == NULL)
		return (1);	

  printf("---- APRES CONCAT ------------------------------------------------------------------------------------ %p -------------\n", curs);

	putsplit(arg);
	father = fork();
	if (!father)
	{
		signals_switch();


		ft_putendl("---LANCEMENT EXECVE / exec_cmd");

		execve(arg[0], arg, (*env)->env);
		ft_putendl("Gros fail");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		ft_putendl("--FIN D EXEC DE COMMANDE / exec_cmd");
		ft_destroy_env(arg);
	}
	return (0);
}

int		ft_exec_pipeline(t_node *curs, t_shenv **env)
{
	(void)curs;
	(void)env;
	return (0);
}


void	process_cmd(t_node *ast, t_shenv **env)
{

	if (!ast)
		return ;

	printf("-DEBUT LECTURE DE TOKEN [%s] %p \n", ast->value, ast);

	if (ast->token == tok_expr)
	{
	  if (exec_cmd(ast, env))
	    ft_putendl("wtf");
	}
	else if (ast->token == tok_pipe)
	{
		ft_exec_pipeline(ast, env);
	}
	//	write(1, "\n\n", 2);//
	//	ft_put_ast(ast, 0);//
		write(1, "\n\n", 2);//
	printf("-FIN DE LECTURE DE TOKEN [%s] %p -- PROCHAIN : %p \n", ast->value, ast, ast->left);


	process_cmd(ast->left, env);

}

