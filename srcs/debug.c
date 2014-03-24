/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 14:40:08 by garm              #+#    #+#             */
/*   Updated: 2014/03/24 19:23:07 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** DISPLAY ABSTRACT SYNTAX TREE
*/
void	ft_put_ast(t_node *tree, int side)
{
	if (!tree)
		return ;
	if (side == 'L')
		ft_putendl("");
	ft_putstr(" -> ");
	ft_putstr(tree->value);
	ft_put_ast(tree->right, 'R');
	ft_put_ast(tree->left, 'L');
}

/*
** DISPLAY LEXING TABLE
*/
char	*ft_toktostr(t_tok token)
{
	char	*str[NB_TOKENS];

	str[0] = "TOK_UNCOMPLETED";
	str[1] = "TOK_EXPR";
	str[2] = "TOK_CMD";
	str[3] = "TOK_ARG";
	str[4] = "TOK_SEPARATOR";
	str[5] = "TOK_HEREDOC";
	str[6] = "TOK_READ";
	str[7] = "TOK_WRITE";
	str[8] = "TOK_APPEND";
	str[9] = "TOK_PIPE";
	str[10] = "TOK_AND";
	str[11] = "TOK_OR";
	str[12] = "TOK_SUBSH";
	str[13] = "TOK_BQUOTE";
	str[14] = "TOK_END";
	str[15] = "TOK_BG";
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

