#include "main.h"

JOB *head = NULL;

/* Insert stopped process into list */
void insert_first(pid_t pid, char *cmd)
{
    JOB *new = malloc(sizeof(JOB));

    if(new == NULL)
    {
        perror("error");
        return;
    }

    new->pid = pid;

    strcpy(new->command, cmd);

    new->link = head;

    head = new;
}

/* Display all jobs */
void print_jobs(void)
{
    JOB *temp = head;

    if(temp == NULL)
    {
        printf("No Jobs\n");
        return;
    }

    printf("PID\tCOMMAND\n");
    printf("------------------------\n");

    while(temp != NULL)
    {
        printf("%d\t%s\n", temp->pid, temp->command);

        temp = temp->link;
    }
}