#include <unistd.h>
#include "42sh.h"

int main(int argc, char **argv)
{
	if (argc > 1)
		return (ft_error(argv[0]));
	ft_putendl("garm main : Lexer...\n");
	return (0);
}

