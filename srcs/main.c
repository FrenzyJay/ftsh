#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "42sh.h"

int main(int argc, char **argv)
{
	char	*line;
	t_node	*ast;

	if (argc > 1)
		return (ft_error(argv[0]));
	while (get_next_line(0, &line) > 0)
	{
		ast = ft_parser(line);
		ast = ft_ast_rewind(ast);
		ft_put_ast(ast, 0);
	}
	return (0);
}

