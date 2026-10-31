#include "main.h"

// Converts a command into an argument array for execvp()
void build_argv(char *cmd, char **argv)
{
    int i = 0;
    char *saveptr;  // Stores the position for strtok_r()

    argv[i] = strtok_r(cmd, " ", &saveptr);  // Gets the first argument

    while(argv[i] != NULL)
    {
        i++;
        argv[i] = strtok_r(NULL, " ", &saveptr);  // Gets the next argument
    }
}

// Executes commands connected using pipes
void execute_pipe(char *input_string)
{
    char *commands[20];  // Stores individual commands
    int count = 0;       // Counts the number of commands

    commands[count] = strtok(input_string, "|");  // Splits input using pipe symbol

    while(commands[count] != NULL)
    {
        count++;
        commands[count] = strtok(NULL, "|");  // Gets the next command
    }

    int pipes[count - 1][2];  // Creates pipe file descriptor array

    // Creates pipes between commands
    for(int i = 0; i < count - 1; i++)
    {
        pipe(pipes[i]);
    }

    // Creates a child process for each command
    for(int i = 0; i < count; i++)
    {
        pid_t pid = fork();

        if(pid == 0)
        {
            /* First Command */
            if(i == 0)
            {
                dup2(pipes[i][1], STDOUT_FILENO);  // Sends output to the pipe
            }

            /* Last Command */
            else if(i == count - 1)
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);  // Takes input from previous pipe
            }

            /* Middle Commands */
            else
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);  // Takes input from previous command
                dup2(pipes[i][1],STDOUT_FILENO);      // Sends output to next command
            }

            /* Close all pipe FDs */
            for(int j = 0; j < count - 1; j++)
            {
                close(pipes[j][0]);  // Closes pipe read end
                close(pipes[j][1]);  // Closes pipe write end
            }

            char *argv[20];  // Stores command and its arguments

            while(*commands[i] == ' ')
            {
                commands[i]++;  // Skips leading spaces
            }

            build_argv(commands[i],argv);  // Converts command into argv format

            execvp(argv[0], argv);  // Executes the command

            perror("execvp");  // Displays error if execution fails
            exit(1);            // Terminates child process on failure
        }
    }

    /* Parent closes all pipes */
    for(int i = 0;i < count - 1;i++)
    {
        close(pipes[i][0]);  // Closes read end in parent
        close(pipes[i][1]);  // Closes write end in parent
    }

    /* Wait for all children */
    for(int i = 0; i < count; i++)
    {
        wait(NULL);  // Waits for a child process to finish
    }
    return;
}