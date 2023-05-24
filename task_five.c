#include "shell.h"

void execute_command(char *args[]) {
    char *envp[] = { NULL };
    int killch;

    // Execute the command
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        if (execve(args[0], args, envp) == -1) {
            fprintf(stderr, "Error: Command '%s' not found.\n", args[0]);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Error occurred
        fprintf(stderr, "Error: Fork failed.\n");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(pid, &killch, 0);
    }
}

int main(void)
{
    char *command;
    char *args[MAX_ARGS];
    int arg_count;
    int killch;

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

        //Check if the user entered the env command
        if (strcmp(command, "env") == 0) {
            // Print the current environment
            char **env = environ;
            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }
        } else {
            // Parse the command line arguments
            char *token = strtok(command, " ");
            arg_count = 0;
            while (token != NULL && arg_count < MAX_ARGS - 1) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " ");
            }
            args[arg_count] = NULL;

            // Check if the command exists before calling fork
            if (command_exists(args[0])) {
                // Get the full path to the command
                char *cmd_path = get_command_path(args[0]);
                if (cmd_path != NULL) {
                    args[0] = cmd_path;
                }

                // Execute the command
                execute_command(args);
            } else {
                // Command not found
                fprintf(stderr, "Error: Command '%s' not found.\n", args[0]);
            }
        }
    }

    free(command);
    return (0);
}
