// Includes the header file containing function declarations and required libraries
#include "main.h"

// Function to change the MiniShell prompt
void copy_change(char *prompt, char *input_string)
{
    // Declares loop variable i and initializes j to 0
    int i, j = 0;

    // Starts reading input_string from index 4, skipping "PS1="
    for(i = 4; input_string[i] != '\0'; i++)
    {
        // Copies each character after "PS1=" into the prompt array
        prompt[j++] = input_string[i];
    }

    // Adds the null character to mark the end of the prompt string
    prompt[j] = '\0';
}