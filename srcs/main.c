#include <unistd.h>
#include "42sh.h"

int	ft_error(char *msg)
{
	int		i;

	i = 0;
	while (msg + i)
		i++;
	write(2, msg, i);
	return (-1);
}

int main(int argc, char **argv)
{
	char	*line;

	if (argc > 1)
		return (ft_error(argv[0]));
	while (get_next_line(0, &line) >= 0)
		ft_printf("entry : %s\n", line);
	return (0);
}

