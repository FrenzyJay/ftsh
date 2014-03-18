#ifndef FTSH_H
# define FTSH_H

# include "libft.h"
# include "parser.h"

/*
** EXEC
*/
int	exec_cmd(char *cmd);

/*
** DEBUG
*/
char	*ft_toktostr(t_tok token);
void	ft_putlex(t_lex *lex);

#endif
