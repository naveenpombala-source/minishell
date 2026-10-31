/*
Name        : Pombala Naveen
Date        : 01-11-2026
Project     : Mini Shell (msh)

Description :
    This project implements a minimalistic command-line shell
    called Mini Shell (msh) as part of the Linux Internal module.

    The main objective of this project is to understand and
    implement Linux system calls related to process creation,
    process execution, process synchronization, signal handling,
    exit status management and inter-process communication.

    The Mini Shell provides a customizable command prompt using
    the PS1 variable and allows users to execute both internal
    and external commands. It supports special variables to
    display the shell process ID, last command exit status and
    shell executable path.

    Built-in commands such as cd, pwd and exit are implemented
    to perform basic shell operations. External commands are
    executed using process creation and execution system calls
    such as fork(), execvp() and waitpid().

    Signal handling is implemented to manage foreground
    processes using SIGINT and SIGTSTP signals through
    keyboard shortcuts Ctrl+C and Ctrl+Z.

    The project also provides background process execution
    using the ampersand (&) operator and job control
    functionalities such as jobs, fg and bg to manage
    running and stopped processes.

    Pipe functionality is implemented using pipe() and dup2()
    system calls to establish communication between multiple
    processes and execute multiple commands in a pipeline.

    Through this project, practical knowledge of Linux
    system programming, process management, signal handling,
    file descriptors, pipes and system calls is gained.
*/

#include "main.h"
#include<stdio.h>
int status = 0;
char *external_commands[200];
pid_t child_pid = 0;

int main()
{
    //clear the screen
    system("clear");
    
    //varible declaration
    //array to store the input
    char input_string[100];

    extract_external_commands(external_commands);
 
    
    //array to store the prompt
    char prompt[25] = "MINISHELL";

    //register the signals
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGCHLD, signal_handler);

    
    //scan the input
    scan_input(prompt, input_string,external_commands);

    return 0;
}