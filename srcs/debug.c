/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 14:40:08 by garm              #+#    #+#             */
/*   Updated: 2014/03/27 01:27:11 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** DISPLAY ABSTRACT SYNTAX TREE
*/
void	ft_put_ast(t_node *ast)
{
	t_node	*temp;
	t_node	*temp_right;

	temp = ast;
	if (ast)
	{
		while (temp)
		{
			ft_putstr("[");
			ft_putstr(ft_toktostr(temp->token));
			ft_putstr("] (");
			ft_putstr(temp->value);
			ft_putstr(")");
			temp_right = temp->right;
			while (temp_right)
			{
				ft_putstr(" -> [");
				ft_putstr(ft_toktostr(temp_right->token));
				ft_putstr("] (");
				ft_putstr(temp_right->value);
				ft_putstr(")");
				temp_right = temp_right->right;
			}
			if (temp->left)
				ft_putendl("\n|\nV");
			temp = temp->left;
		}
	}
}

/*
** DISPLAY LEXING TABLE
*/
char	*ft_toktostr(t_tok token)
{
	char	*str[NB_TOKENS];

	str[0] = "SEPARATOR";
	str[1] = "UNCOMPLETED";
	str[2] = "EXPR";
	str[3] = "HEREDOC";
	str[4] = "READ";
	str[5] = "WRITE";
	str[6] = "APPEND";
	str[7] = "CMD";
	str[8] = "ARG";
	str[9] = "PIPE";
	str[10] = "AND";
	str[11] = "OR";
	str[12] = "SUBSH";
	str[13] = "END";
	str[14] = "BG";
	return (str[token]);
}

void	ft_putlex(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		ft_putstr("{");
		ft_putstr(ft_toktostr(tmp->token));
		ft_putstr("} -> [");
		ft_putstr(tmp->value);
		ft_putendl("]");
		tmp = tmp->next;
	}
}

