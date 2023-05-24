#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

#define MAXLINE 1024 /* max length of a command line */
#define MAXARGS 64 /* max number of arguments in a command line */

/* evaluate a command line */
void eval(char *cmdline);

/* parse the command line and build the argument list */
int parseline(char *buf, char **argv);

/* check if the command is a built-in command and execute it if so */
int builtin_command(char **argv);

/* Declare your function prototype here */
int print_environment_variables(void);

#endif /* SHELL_H */
