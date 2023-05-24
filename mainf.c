#include "shell.h"

int main(void)
{
    char cmdline[MAXLINE]; /* buffer for the command line */

    while (1) {
        /* display a prompt and wait for the user to type a command */
        printf("> ");
        fflush(stdout);

        /* read the command line */
        if (fgets(cmdline, MAXLINE, stdin) == NULL)
            break; /* handle end of file condition */

        /* evaluate the command line */
        eval(cmdline);
    }

    return 0;
}
