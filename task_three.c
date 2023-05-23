#include "shell.h"

// Function to search for the command in the directories specified by PATH 
char *get_command_path(char *command) { 
    char *path = getenv("PATH"); 
    char *dir = strtok(path, ":"); 
 
    while (dir != NULL) { 
        // Construct the full path to the command 
        char cmd_path[MAX_COMMAND_LENGTH]; 
        strcpy(cmd_path, dir); 
        strcat(cmd_path, "/"); 
        strcat(cmd_path, command); 
 
        // Check if the command exists at this path 
        if (access(cmd_path, F_OK) == 0) { 
            // Command found, return the path 
            return strdup(cmd_path); 
        } 
 
        dir = strtok(NULL, ":"); 
    } 
 
    // Command not found 
    return NULL; 
} 
 
// Function to check if the command exists before calling fork 
int command_exists(char *command) { 
    char *path = getenv("PATH"); 
    char *dir = strtok(path, ":"); 
 
    while (dir != NULL) { 
        // Construct the full path to the command 
        char cmd_path[MAX_COMMAND_LENGTH]; 
        strcpy(cmd_path, dir); 
        strcat(cmd_path, "/"); 
        strcat(cmd_path, command); 
 
        // Check if the command exists at this path 
        if (access(cmd_path, F_OK) == 0)        { 
            // Command found 
            return 1; 
        } 
 
        dir = strtok(NULL, ":"); 
    } 
 
    // Command not found 
    return 0; 
}
