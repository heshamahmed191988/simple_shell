#include "shell.h"

/* check if the command is a built-in command and execute it if so */
int builtin_command(char **argv)
{
	if (!strcmp(argv[0], "exit"))
	{ /* exit command */
		exit(0);
	}
	if (!strcmp(argv[0], "env"))
	{ /* env command */
		char **environ; /* pointer to environment variables array */
		int i = 0;

		while (environ[i])
		{ /* print each environment variable on a new line */
			printf("%s\n", environ[i++]);
		}
		return (1);
	}
	return (0); /* not a built-in command */
}
