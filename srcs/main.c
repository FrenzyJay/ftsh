#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "42sh.h"

int main(int argc, char **argv)
{
	char	*line;
	t_lex	*lex;

	if (argc > 1)
		return (ft_error(argv[0]));
	while (get_next_line(0, &line) > 0)
	{
		lex = ft_lexer(ft_strdup(line), NULL);
		ft_memdel((void **)&line);
		ft_putlex(lex);
		ft_lex_destroy(&lex);
	}
	return (0);
}

