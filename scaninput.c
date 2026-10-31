#include "main.h"

// Reads user input and identifies which command to execute
void scan_input(char *prompt, char *input_string, char **external_commands)
{
    char *command;
    int type;
    int i;

    while(1)  // Keeps the shell running continuously
    {
        input_string[0] = '\0';  // Clears previous input
        printf(ANSI_COLOUR_RED "%s> " ANSI_COLOUR_RESET, prompt);  // Displays shell prompt

        if(fgets(input_string, 100, stdin) == NULL)  // Reads input from user
        {
            clearerr(stdin);  // Clears input error or EOF flag
            continue;
        }

        // Removes newline character from input
        for(i = 0; input_string[i] != '\0'; i++)
        {
            if(input_string[i] == '\n')
            {
                input_string[i] = '\0';
                break;
            }
        }

        if(strncmp(input_string, "PS1=", 4) == 0)  // Checks for prompt change command
        {
            copy_change(prompt, input_string);  // Changes the shell prompt
            continue;
        }

        if(strchr(input_string, '|') != NULL)  // Checks whether input contains a pipe
        {
            execute_pipe(input_string);  // Executes piped commands
            continue;
        }

        command = get_command(input_string);  // Extracts the command name

        type = check_command_type(command,external_commands);  // Identifies command type

        if(type == BUILDIN)
        {
            execute_internal_command(input_string);  // Executes built-in command
        }
        else if(type == EXTERNAL)
        {
            execute_external_command(input_string);  // Executes external command
        }
        else
        {
            printf("%s : Command not found\n", command);  // Displays error for unknown command
        }
    }
}