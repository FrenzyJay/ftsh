#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "42sh.h"

int main(int argc, char **argv)
{
	char	*line;

	if (argc > 1)
		return (ft_error(argv[0]));
	while (get_next_line(0, &line) > 0)
	{
		ft_parser(line);
	}
	return (0);
}

