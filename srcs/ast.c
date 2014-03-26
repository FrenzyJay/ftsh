/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/20 05:11:51 by garm              #+#    #+#             */
/*   Updated: 2014/03/24 18:40:25 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

t_node		*ft_ast_add(t_node *tree, t_lex *elem, char side)
{
	t_node		*new;

	if (!elem)
		return (tree);
	new = (t_node *)ft_memalloc(sizeof(t_node));
	new->token = elem->token;
	new->value = elem->value;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	if (tree)
	{
		new->parent = tree;
		if (side == 'L')
			tree->left = new;
		else if (side == 'R')
			tree->right = new;
	}
	return (new);
}

t_node		*ft_ast_rewind(t_node *tree)
{
	if (tree)
	{
		while (tree && tree->parent != NULL)
			tree = tree->parent;
	}
	return (tree);
}

