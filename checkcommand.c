#include "main.h"

//To findout the type command -> internal,external, no command
int check_command_type(char *command,char**external_commands)
{
    //list buildincommand
    char *builtins[] ={"echo","printf","read","cd","pwd","pushd","popd","dirs","let","eval","set","unset","export","declare","typecast","readonly","getopts","source","exit","exec","shopt","caller","true","type","hash","bind","help","jobs","bg","fg",NULL};
    
    for(int i = 0 ; builtins[i] != NULL ; i++)
    {
        if(strcmp(command,builtins[i]) == 0)
        {
            return BUILDIN;
        }
    }

    //ENTER KEY    
    if(strcmp(command,"\0") == 0)        
    {
        return NO_COMMAND;       
    }
   
   
    //to extract the external commands
   for(int i = 0 ; external_commands[i] != NULL ; i++)
    {
        if(strcmp(command,external_commands[i]) == 0)
        {
            return EXTERNAL;
        }
    }
        return NO_COMMAND;
}