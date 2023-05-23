#include "shell.h"

extern char **environ;

int main(void)
{
        char *command;
        char *args[2];
        char *envp[] = { NULL };
        int status;

        while (1) {
                // Display prompt and wait for user input
                printf("$ ");
                fflush(stdout);

                // Read user input
                size_t bufsize = 0;
                getline(&command, &bufsize, stdin);

                // Remove newline character from input
                command[strcspn(command, "\n")] = '\0';

                // Exit on EOF (Ctrl+D)
                if (!command) {
                        break;
                }

                // Handle env command
                if (strcmp(command, "env") == 0) {
                        char **env = environ;

                        while (*env) {
                                printf("%s\n", *env);
                                env++;
                        }

                        continue;
                }

                // Execute the command
                pid_t pid = fork();

                if (pid == 0) {
                        // Child process
                        args[0] = command;
