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
