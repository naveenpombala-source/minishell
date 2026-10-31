#include "main.h"

extern int status;  // Accesses global exit status

// Function to execute built-in commands
void execute_internal_command(char *input_string)
{
    char ch[100];   // Stores current directory
    char *path;     // Stores directory path

    char *command = get_command(input_string);

    // Implements pwd command
    if(strcmp(command, "pwd") == 0)
    {
        getcwd(ch, sizeof(ch));
        printf("%s\n", ch);
    }

    // Exits the MiniShell
    else if(strcmp(command, "exit") == 0)
    {
        exit(0);
    }

    // Implements cd command
    else if(strcmp(command, "cd") == 0)
    {
        path = strtok(input_string, " ");
        path = strtok(NULL, " ");

        if(path != NULL)
        {
            if(chdir(path) != 0)
            {
                perror("cd");
            }
        }
    }

    // Implements echo command
    else if(strcmp(command, "echo") == 0)
    {
        echo(input_string, status);
    }

    // Displays stored jobs
    else if(strcmp(command, "jobs") == 0)
    {
        print_jobs();
    }

    // Brings a stopped job to the foreground
    else if(strcmp(input_string, "fg") == 0)
    {
        if(head == NULL)
        {
            printf("No Jobs\n");
            return;
        }

        printf("%s\n", head->command);

        child_pid = head->pid;

        // Resumes the stopped process
        kill(head->pid, SIGCONT);

        // Waits for the resumed process
        waitpid(head->pid, &status, WUNTRACED);
    }

    // Resumes a stopped job in the background
    else if(strcmp(input_string, "bg") == 0)
    {
        if(head == NULL)
        {
            printf("No Jobs\n");
            return;
        }

        kill(head->pid, SIGCONT);

        printf("%d Running %s\n",head->pid, head->command);
    }
}