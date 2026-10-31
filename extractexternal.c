#include "main.h"

void extract_external_commands(char **external_commands)
{
    //varible declaration
    char ch;
    char buffer[25] = {'\0'};
    int i = 0 , j = 0;

    //open the file
    int fd = open("external_commands.txt",O_RDONLY);

    if(fd == -1)
    {
        printf("open : Failed");
        exit(1);
    }
    //read the commands from the file
    while(read(fd,&ch,1) > 0)
    {
        if(ch != '\n' && ch!='\r')
        {
            buffer[i++] = ch;
        }
        else
        {
            //allocate the memory
            external_commands[j] = calloc(strlen(buffer)+1,sizeof(char));

            //copy the contents
            strcpy(external_commands[j],buffer);
            j++;

             //clear the buffer
            memset(buffer,'\0',25);

            i = 0;
        }

    }
    /* Last command */
    if(strlen(buffer))
    {
        external_commands[j] =
                calloc(strlen(buffer) + 1,
                       sizeof(char));

        strcpy(external_commands[j], buffer);

        j++;
    }

    external_commands[j] = NULL;

    close(fd); 
}