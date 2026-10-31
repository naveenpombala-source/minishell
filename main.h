#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>


#define BUILDIN    1
#define EXTERNAL   2
#define NO_COMMAND 3


typedef struct node
{
    pid_t pid;
    char command[50];

    struct node *link;

}JOB;


#define ANSI_COLOUR_RED     "\x1b[31m"
#define ANSI_COLOUR_GREEN   "\x1b[32m"
#define ANSI_COLOUR_YELLOW  "\x1b[33m"
#define ANSI_COLOUR_BLUE    "\x1b[34m"
#define ANSI_COLOUR_MAGENTA "\x1b[35m"
#define ANSI_COLOUR_CYAN    "\x1b[36m"
#define ANSI_COLOUR_RESET   "\x1b[0m"



// Declares the global array that stores external command names
extern char *external_commands[200];
// Declares the global variable that stores the child process ID
extern pid_t child_pid;
// Declares the head pointer of the jobs linked list
extern JOB *head;

//function declartion
void scan_input(char *prompt, char *input_string,char**external_commands);
char *get_command(char *input_string);
void copy_change(char *prompt,char *input_string);
int check_command_type(char *command,char**external_commands);
void echo(char *input_string, int status);
void execute_internal_command(char *input_string);
void extract_external_commands(char **external_commands);
void execute_external_command(char *input_string);
void execute_pipe(char *input_string);
void signal_handler(int sig_num);
void insert_first(pid_t pid, char *cmd);
void print_jobs(void);


#endif