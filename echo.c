#include "main.h"

// Function to implement special echo commands
void echo(char *input_string, int status)
{
    // Prints the current process ID
    if(strcmp(input_string, "echo $$") == 0)
    {
        printf("%d\n", getpid());
    }
    // Prints the exit status of the last command
    else if(strcmp(input_string, "echo $?") == 0)
    {
        printf("%d\n", status);
    }
    // Prints the shell environment variable
    else if(strcmp(input_string,"echo $SHELL")==0)
    {
        printf("%s\n", getenv("SHELL"));
    }
}