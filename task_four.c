#include "shell.h"

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

                // Handle exit command
                if (strcmp(command, "exit") == 0) {
                        break;
                }

                // Execute the command
                pid_t pid = fork();

                if (pid == 0) {
                        // Child process
                        args[0] = command;
                        args[1] = NULL;

                        if (execve(command, args, envp) == -1) {
                                fprintf(stderr, "Error: Command '%s'' not found.\n", command);
                                exit(EXIT_FAILURE);
                        }
                } else if (pid < 0) {
                        // Error occurred
                        fprintf(stderr, "Error: Fork failed.\n");
                        exit(EXIT_FAILURE);
                } else {
                        // Parent process
                        waitpid(pid, &status, 0);
                }
        }

        free(command);
        return (0);
}

