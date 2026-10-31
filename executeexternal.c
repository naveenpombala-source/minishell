#include "main.h"

// Function to execute external commands
void execute_external_command(char *input_string)
{
    char *argv[20];  // Stores command and arguments
    int i = 0;

    pid_t pid;       // Stores process ID
    int status;      // Stores child process status

    char temp[100];

    // Saves the original command before tokenizing
    strcpy(temp, input_string);

    // Extracts the command name
    argv[i] = strtok(input_string, " ");

    // Extracts remaining arguments
    while(argv[i] != NULL)
    {
        i++;
        argv[i] = strtok(NULL, " ");
    }

    int bg_flag = 0;  // Checks whether background execution is requested

    // Searches for the '&' symbol
    for(i = 0; argv[i] != NULL; i++)
    {
        if(strcmp(argv[i], "&") == 0)
        {
            bg_flag = 1;
            argv[i] = NULL;  // Removes '&' from arguments
            break;
        }
    }

    // Creates a child process
    pid = fork();
    child_pid = pid;

    if(child_pid > 0)
    {
        // Handles background execution
        if(bg_flag)
        {
            insert_first(child_pid, temp);
            printf("[%d] Running in Background\n",child_pid);
        }
        else
        {
            // Waits for foreground child process
            waitpid(child_pid, &status, WUNTRACED);

            // Checks whether the child is stopped
            if(WIFSTOPPED(status))
            {
                printf("\nChild Stopped : %d\n", child_pid);
                insert_first(child_pid, input_string);
                
            }
            // Gets the child's exit status
            else if(WIFEXITED(status))
            {
                status = WEXITSTATUS(status);
            }
        }
    }
    else if(child_pid == 0)
    {
        // Executes the external command
        execvp(argv[0], argv);

        // Prints error if execution fails
        perror("execvp");
        exit(1);
    }
    else
    {
        // Prints error if fork fails
        perror("fork");
    }
}