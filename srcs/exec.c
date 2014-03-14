#include <unistd.h>

int	exec_cmd(char *comd)
{
	char	*cmd = "/bin/ls";
	char	*arg[] = {"ls", "-l", NULL};

	(void)comd;
	execve(cmd, arg, NULL);
	return (0);
}

