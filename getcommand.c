#include "main.h"

// Function to extract the first word from user input
char *get_command(char *input_string)
{
    static char command[100];  // Stores extracted command
    int i;

    // Copies characters until a space or null character
    for(i = 0; input_string[i] != '\0'; i++)
    {
        if(input_string[i] == ' ')
        {
            break;
        }

        command[i] = input_string[i];
    }

    // Terminates the command string
    command[i] = '\0';

    return command;  // Returns extracted command
}