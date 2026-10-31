#include "main.h"

// Handles signals received by the MiniShell
void signal_handler(int sig_num)
{
    int status;  // Stores child process status
    pid_t pid;   // Stores process ID

    if(sig_num == SIGINT)  // Checks for Ctrl+C signal
    {
        if(child_pid > 0)
        {
            kill(child_pid, SIGINT);  // Sends interrupt signal to child
        }
        else
        {
            printf("\nMINISHELL> ");  // Displays prompt again
            fflush(stdout);           // Immediately displays output
        }
    }

    else if(sig_num == SIGTSTP)  // Checks for Ctrl+Z signal
    {
        if(child_pid > 0)
        {
            kill(child_pid, SIGTSTP);  // Sends stop signal to child
        }
        else
        {
            printf("\nMINISHELL> ");  // Displays prompt again
            fflush(stdout);           // Immediately displays output
        }
    }

    else if(sig_num == SIGCHLD)
    {
        pid = waitpid(-1, &status, WNOHANG);

        if(pid > 0 && WIFEXITED(status))
        {
            printf("Exit code: %d\n", WEXITSTATUS(status));
        }
    }
}