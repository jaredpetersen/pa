/*

Jane -- Your Personal Computer Assistant

Created by Jared Petersen
Please see README and LICENSE for more information

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *formatCommand(int count, char **arguments);
void learnCommand(void);
void forgetCommand(void);
void runCommand(char inputCommand[]);
void badCommand(void);


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
        system("echo \"Yes, $(whoami)? :)\"");
    }
    else if (argc >= 2)
    {
        // Arguments are split up by spaces
        // Format all of the arguments as one string
        char *command = formatCommand(argc, argv);

        if (strcasecmp(command, "learn") == 0)
        {
            // Learn a new command
            learnCommand();
        }
        else if (strcasecmp(command, "forget") == 0)
        {
            // Forget an existing command
            forgetCommand();
        }
        else
        {
            // Run the command
            runCommand(command);
        }
    }

    return 0;
}

/*
Format the command string by combining all of the terminal arguments
*/
char *formatCommand(int count, char **arguments) {
    static char command[100];
    for (int i = 1; i < count; i++)
    {
        if (i == 1)
        {
            // First iteration, copy the string into command
            strcpy(command, arguments[i]);
        }
        else
        {
            // Everything else, add it on the the existing string
            strcat(command, arguments[i]);
        }

        if (i != count - 1)
        {
            // Add a space at the end for each of the arguments
            // with the exception of the last one
            strcat(command, " ");
        }
    }
    return command;
}

/*
Adds a new command to the list of available commands
*/
void learnCommand()
{
    printf("I cannot learn a new command at the moment.\n");
}

/*
Removes a new command from the list of available commands
*/
void forgetCommand()
{
    printf("I cannot forget a command at the moment.\n");
}

/*
Runs the command if it exists
*/
void runCommand(char *inputCommand)
{
    // Begin process of retrieving all possible commands
    FILE *commandFile;
    commandFile = fopen("./commands/commands.txt", "r");
    char command[100];
    char action[100];

    // Make sure that that we actually found the commands file
    if (commandFile == NULL)
    {
        // File wasn't found
        // Act as if we don't know that command (technically we know nothing...)
        badCommand();
    }

    // Loop over the lines in the file
    // Went with ::::: as a separator because it's highly unlikely that
    // would need to be in part of a commdand or action
    bool found = false;
    while ((fscanf(commandFile, "%[^:::::]:::::%[^\n]\n", command, action) != EOF) && (!found))
    {
        // Check if the command on this line is the same
        if ((strcasecmp(inputCommand, command) == 0))
        {
            // Command exists, call off the search and run it
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
    printf("I'm not sure what you mean :(\n");
}
