/*

Computer Personal Assistant
Please see README and LICENSE for more information

Created by Jared Petersen

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void badCommand(void);
void runCommand(char inputCommand[], char inputTarget[]);

/*
Main method
Evaluates the arguments and runs the necessary commands
*/
int main(int argc, char **argv)
{
    // Initialize the personal assistant
    if (argc == 1)
    {
        // User only called the application, no arguments
        printf("What's up?\n");
    }
    else if (argc == 2)
    {
        // User called the application with one argument
        // One argument commands not yet supported
        printf("Can you be more specific?\n");
    }
    else if (argc == 3)
    {
        // User called the application with two arguments
        // Two argument commands are supported
        runCommand(argv[1], argv[2]);
    }
    else if (argc > 3)
    {
        // User called the application with more than two arguments
        // Behavior not yet supported
        badCommand();
    }

    return 0;
}

/*
Runs the command if it exists
*/
void runCommand(char inputCommand[], char inputTarget[])
{
    // Begin process of retrieving all possible commands
    FILE *commandFile;
    commandFile = fopen("./commands/commands.txt", "r");
    char command[50];
    char target[50];
    char action[100];

    // Make sure that that we actually found the commands file
    if (commandFile == NULL)
    {
        // File wasn't found
        // Act as if we don't know that command (technically we know nothing...)
        badCommand();
    }

    // Loop over the lines in the file
    bool found = false;
    while ((fscanf(commandFile, "%s %s : %[^\n]s", command, target, action) != EOF) &&
           (!found))
    {
        // Check if the command on this line is the same
        if ((strcmp(inputCommand, command) == 0) &&
            (strcmp(inputTarget, target) == 0))
        {
            // Command and target exists, call off the search and run it
            found = true;
            system(action);
        }
    }

    // Check if the command was ever found
    if (found == false)
    {
        // Command does not exist, let the user know
        badCommand();
    }

    // Close the file
    fclose(commandFile);
}

/*
Tells the user that the command does not exist
*/
void badCommand() {
    printf("I don't know how to do that :-(\n");
}
