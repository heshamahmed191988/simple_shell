#include "shell.h"

/**
  * parseline - parseline
  * @argv: value
  * @buf: buf
  *
  * Return: null acording to void
  */

/* parse the command line and build the argument list */
int parseline(char *buf, char **argv)
{
	char *delim; /* points to first space delimiter */
	int argc; /* number of arguments */
	int bg; /* background job? */

	buf[strlen(buf) - 1] = ' '; /* replace trailing '\n' with space */
	while (*buf && (*buf == ' ')) /* ignore leading spaces */
		buf++;

	/* build the argument list */
	argc = 0;
	while ((delim = strchr(buf, ' ')))
	{
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) /* ignore spaces */
			buf++;
	}
	argv[argc] = NULL;

	if (argc == 0)
	{/* ignore blank line */
		return (1);
	}

	/* check if background job */
	if ((bg = (*argv[argc - 1] == '&')) != 0)
		argv[--argc] = NULL;
	{
	return (bg);
	}
}
