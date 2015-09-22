/*

Computer Personal Assistant
Please see README and LICENSE for more information

Created by Jared Petersen

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


bool validCommand(char command[]);
void invalidRequestErr(void);

/*
Main method
Evaluates the arguments and runs the necessary commands
*/
int main(int argc, char **argv)
{
    // Begin evaluating the commands
    if (argc == 1)
    {
        // They didn't ask us anything
        printf(">> What's up?\n");
    }
    else if (argc == 2)
    {
        // They asked us to do something
        // Make sure the command is valid
        if (validCommand(argv[1]))
        {
            // Ask for clarification since the command is too short
            //char* newstring = argv[1];
            //newstring[0] = 'S';
            printf(">> %s what?\n", argv[1]);
        }
        else
        {
            // Tell them that it's not a valid request
            invalidRequestErr();
        }
    }
    else
    {
        // They asked us to do something
        // Make sure the command is valid
        if (validCommand(argv[1]) &&
            strcmp(argv[1], "open") == 0 &&
            strcmp(argv[2], "firefox") == 0)
        {
            // Open FireFox
            system("open '/Applications/Firefox.app'");
        }
        else {
            // Tell them that it's not a valid request
            invalidRequestErr();
        }
    }

    return 0;
}

/*
Rudimentary check to make sure the commands issued are valid
Will need the program to check a file for a list of commands in the future
*/
bool validCommand(char command[])
{
    if (strcmp(command, "open") == 0 ||
        strcmp(command, "learn") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
Prints an error message to let users know they didn't use a valid command
*/
void invalidRequestErr(void) {
    printf("Invalid command\n");
}
