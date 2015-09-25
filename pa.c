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
void promptUserValue(char *responseVar, char prompt[]);
bool checkCommandExists(char inputCommand[]);
void badCommand(void);
void fileNotFound(void);

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
char *formatCommand(int count, char **arguments)
{
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
    // Prompt the user for the command and save it to command
    char command[100];
    promptUserValue(command, "What is the command that you would like me to learn?");

    // Prompt the user for the linux action and save it to action
    char action[100];
    promptUserValue(action, "What is the terminal command that you would like it to execute?");

    // Open up the command file for appending and reading
    FILE *commandFile;
    commandFile = fopen("./commands/commands.txt", "a+");

    // Make sure that that we actually found the commands file
    if (commandFile == NULL)
    {
        // File wasn't found
        fileNotFound();
    }

    // Make sure the command doesn't already exist
    if (checkCommandExists(command) == true)
    {
        printf("That command already exists\n");
    }
    else
    {
        // Set up the command string for output
        strcat(command, ":::::");
        strcat(action, "\n");
        strcat(command, action);
        //strcat(command, "ls\n");
        // Write to the file
        fprintf(commandFile, "%s", command);
        printf("Command learned\n");
    }

    // Close the file
    fclose(commandFile);
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
        fileNotFound();
    }

    // Loop over the lines in the file
    // Went with ::::: as a separator because it's highly unlikely that
    // would need to be in part of a commdand or action
    bool found = false;
    while ((fscanf(commandFile, "%[^:]:::::%[^\n]\n", command, action) != EOF) && (!found))
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
Prompt the user for a value and save it to the variable responseVar
*/
void promptUserValue(char *responseVar, char *prompt)
{
    // Would normally use malloc, but we can't do that here since the function
    // is called multiple times in succession and the memory can't be freed
    // in between
    printf("%s\n> ", prompt);
    fgets(responseVar, 100, stdin);

    // Make sure they actually gave us something
    // TODO Figure out a way to also deal with only spaces
    if (strcasecmp("\n", responseVar) == 0)
    {
        // User sent us nothing
        printf("I'm sorry, but that's not a valid input :(\n");
        exit(1);
    }
    else
    {
        // Remove the trailing newline that fgets tacks on
        // TODO Figure out a way to remove unecessary spaces
        int length = strlen(responseVar);
        if (length > 0)
        {
            if (responseVar[length-1] == '\n')
            {
                responseVar[length-1] ='\0';
            }
        }
    }
}

/*
Check if the command exists
*/
bool checkCommandExists(char inputCommand[])
{
    // Check for built in commands
    if (strcasecmp(inputCommand, "learn") == 0)
    {
        return true;
    }
    // Check for external commands
    else
    {
        FILE *commandFile;
        commandFile = fopen("./commands/commands.txt", "r");

        char command[100];
        char action[100]; // Including because it makes the fscanf stuff easier
        while (fscanf(commandFile, "%[^:]:::::%[^\n]\n", command, action) != EOF)
        {
            // Check if the command on this line is the same
            if (strcasecmp(inputCommand, command) == 0)
            {
                // Close the file
                fclose(commandFile);

                // Command exists, call off the search and run it
                return true;
            }
        }
        // Close the file
        fclose(commandFile);

        // Command does not exist
        return false;
    }
}

/*
Tells the user that the command does not exist
*/
void badCommand()
{
    printf("I'm not sure what you mean :(\n");
}

/*
Tells the user that it could not find the commands file
*/
void fileNotFound()
{
    printf("I can't seem to find my commands :(\n");
}
