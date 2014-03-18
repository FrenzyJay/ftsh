/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 09:10:05 by garm              #+#    #+#             */
/*   Updated: 2014/03/18 12:36:43 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

char	*ft_gettok(t_tok token)
{
	if (token == TOK_UNCOMPLETED)
		return ("TOK_UNCOMPLETED");
	else if (token == TOK_EXPR)
		return ("TOK_EXPR");
	else if (token == TOK_CMD)
		return ("TOK_CMD");
	else if (token == TOK_ARG)
		return ("TOK_ARG");
	else if (token == TOK_SEPARATOR)
		return ("TOK_SEPARATOR");
	else if (token == TOK_HEREDOC)
		return ("TOK_HEREDOC");
	else if (token == TOK_READ)
		return ("TOK_READ");
	else if (token == TOK_WRITE)
		return ("TOK_WRITE");
	else if (token == TOK_APPEND)
		return ("TOK_APPEND");
	else if (token == TOK_PIPE)
		return ("TOK_PIPE");
	else if (token == TOK_AND)
		return ("TOK_AND");
	else if (token == TOK_OR)
		return ("TOK_OR");
	else if (token == TOK_SUBSH)
		return ("TOK_SUBSH");
	else if (token == TOK_BQUOTE)
		return ("TOK_BQUOTE");
	else if (token == TOK_END)
		return ("TOK_END");
	else if (token == TOK_BG)
		return ("TOK_BG");
	else
		return ("BAD TOKEN");
}

void	ft_putlex(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		ft_putstr("{");
		ft_putstr(ft_gettok(tmp->token));
		ft_putstr("} -> [");
		ft_putstr(tmp->value);
		ft_putendl("]");
		tmp = tmp->next;
	}
}

int		ft_getsize_separator(char *entry)
{
	int		i;

	i = 0;
	while (entry[i] && (entry[i] == ' ' || entry[i] == '\t'))
		i++;
	return (i);
}

int		ft_is_uncompleted(char *value)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (value && value[i])
	{
		if (value[i] == '\\')
			i++;
		else if ((FT_ISQUOTE(value[i]) || value[i] == '(') && quote == 0)
			quote = value[i];
		else if ((FT_ISQUOTE(value[i]) || value[i] == ')') && quote != 0)
			quote = 0;
		i++;
	}
	if (quote == 0 && value[0] != ')')
		return (0);
	else
		return (1);
}

