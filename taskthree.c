#include "shell.h"

/* evaluate a command line */
void eval(char *cmdline)
{
    char *argv[MAXARGS]; /* argument list for execve */
    char buf[MAXLINE]; /* holds modified command line */
    int bg; /* background job? */
    pid_t pid; /* process id */

    strcpy(buf, cmdline); /* copy the command line to the buffer */
    bg = parseline(buf, argv); /* parse the buffer and fill the argument list */

    if (argv[0] == NULL)
        return; /* ignore empty lines */

    if (!builtin_command(argv)) { /* if not a built-in command */
        if ((pid = fork()) == 0) { /* child runs the command */
            if (execvp(argv[0], argv) < 0) { /* execute the command */
                printf("%s: Command not found.\n", argv[0]); /* handle errors */
                exit(0);
            }
        }

        /* parent waits for foreground job to terminate */
        if (!bg) {
            int status;
            if (waitpid(pid, &status, 0) < 0)
                perror("waitfg: waitpid error");
        }
        else
            printf("%d %s", pid, cmdline); /* print process id for background job */
    }

    return;
}
