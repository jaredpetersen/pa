/*

Your Personal Computer Assistant

Created by Jared Petersen
Please see README and LICENSE for more information

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define fileFormatBoth "%[^\x001F]\x001F%[^\x001E]\x001E"
#define fileFormatCommand "%[^\x001F]\x001F%*[^\x001E]\x001E"

void runCommand(char *inputCommand);
void learnCommand(void);
void forgetCommand(void);
void promptUserValue(char *responseVar, char *prompt, bool checkCommand);
void formatCommand(char *command, int count, char **arguments);
bool checkCommandExists(char *inputCommand);
bool validString(char *inputCommand, bool checkSingleQuote);
void formatWriteString(char *output, char *command, char *action);
void getFilePath(char *filePath);
void getTempFilePath(char *filePath);
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
        char command[100];
        formatCommand(command, argc, argv);

        // Execute the command
        // Check through the built-in commands first, then go check the
        // ones in the file
        if (strcasecmp(command, "learn command") == 0)
        {
            // Learn a new command
            learnCommand();
        }
        else if (strcasecmp(command, "forget command") == 0)
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
Runs the command if it exists
*/
void runCommand(char *inputCommand)
{
    // Begin process of retrieving all possible commands from the commands file
    // Get the file path
    char directory[100];
    getFilePath(directory);

    // Set up the file
    FILE *commandFile;
    commandFile = fopen(directory, "r");

    // Make sure that that we actually found the commands file
    if (commandFile == NULL)
    {
        // File wasn't found
        // Act as if we don't know that command (technically we know nothing...)
        fileNotFound();
    }

    // Loop over the lines in the file
    // Went with ASCII delimiters as because it's a fairly good solution to the
    // delimiter collision issue, even though it means users won't be able to
    // edit the commands file on their own
    char command[100];
    char action[100];
    bool found = false;
    while ((fscanf(commandFile, fileFormatBoth, command, action)
        != EOF) && (!found))
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
Adds a new command to the list of available commands
*/
void learnCommand()
{
    // Open the commands file up to make sure we can even learn a command
    // (and for later use in writing to it)
    // Get the file path
    char directory[100];
    getFilePath(directory);
    FILE *commandFile;
    commandFile = fopen(directory, "a+");
    if (commandFile == NULL)
    {
        // File wasn't found/wasn't able to be created
        fileNotFound();
    }

    // Looks like we made it, prompt the user for the command and save it
    char command[100];
    promptUserValue(command, "What command would you like me to learn?", true);

    // Make sure the command doesn't already exist in the file
    if (checkCommandExists(command) == true)
    {
        printf("That command already exists\n");
        exit(1);
    }
    else
    {
        // The command does not exist, we can add it
        // Prompt the user for the linux command and save it to action
        char action[100];
        promptUserValue(action,
            "What's the terminal command that you want it to execute?", false);

        // Set up the command string for output
        char writeString[100];
        formatWriteString(writeString, command, action);

        // Write to the file
        fprintf(commandFile, "%s", writeString);

        // Close the file
        fclose(commandFile);

        // Success!
        printf("Learned command\n");
    }
}

/*
Removes a new command from the list of available commands
*/
void forgetCommand()
{
    // Open up the command file to see if we can even forget a command
    // (and for later use)
    // Get the file path
    char directory[100];
    getFilePath(directory);
    FILE *readFile;
    readFile = fopen(directory, "r");
    if (readFile == NULL)
    {
        // File wasn't found
        fileNotFound();
    }

    char inputCommand[100];
    promptUserValue(inputCommand, "What command would you like me to forget?",
        true);

    // Make sure the command doesn't already exist
    if (checkCommandExists(inputCommand) == true)
    {
        // Open up a new command file that will take the place of the old one
        // Get the file path
        char directoryTemp[100];
        getFilePath(directoryTemp);
        FILE *writeFile;
        writeFile = fopen(directoryTemp, "w");

        // Make sure that that we are able to write a new file
        if (writeFile == NULL)
        {
            // Not able to write to disk
            printf("You haven't given me the permissions to do that :(");
            exit(1);
        }

        // Write the old data to the temp file but exclude the stuff we are
        // forgetting
        char tempCommand[100];
        char tempAction[100];
        char writeString[100];
        while (fscanf(readFile, fileFormatBoth, tempCommand,
            tempAction) != EOF)
        {
            // Check if the command on this line is the same
            if ((strcasecmp(inputCommand, tempCommand) != 0))
            {
                // Not the section that needs to be deleted, add it
                // Prepare the string for writing
                formatWriteString(writeString, tempCommand, tempAction);

                // Write to the temp file
                fprintf(writeFile, "%s", writeString);

                // Reset the write string
                memset(&writeString[0], 0, sizeof(writeString));
            }
        }

        // Close the files
        fclose(readFile);
        fclose(writeFile);

        // Remove the old file and rename the new one
        remove(directory);
        rename(directoryTemp, directory);

        // Success!
        printf("Forgot command\n");
    }
    else
    {
        printf("That command does not exist\n");
        exit(1);
    }
}

/*
################################################################################
Supporting Methods
################################################################################
*/

/*
Prompt the user for a value and save it to the variable responseVar

Would normally use malloc, but we can't do that here since the function
is called multiple times in succession and the memory can't be freed
in between
*/
void promptUserValue(char *responseVar, char *prompt, bool checkCommand)
{
    // Set up the prompt
    printf("%s\n> ", prompt);
    fgets(responseVar, 100, stdin);

    bool isValid;
    if (checkCommand)
    {
        isValid = validString(responseVar, true);
    }
    else
    {
        isValid = validString(responseVar, false);
    }

    // Make sure they actually gave us something
    if (!isValid)
    {
        // User sent us nothing
        printf("I'm sorry, but that's not a valid input :(\n");
        exit(1);
    }
    else
    {
        // Remove the trailing newline that fgets tacks on
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
Format the command string by combining all of the terminal arguments into one
string
*/
void formatCommand(char *command, int count, char **arguments)
{
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
}

/*
Check if the command exists
Return true if the command exists or false if it does not
*/
bool checkCommandExists(char *inputCommand)
{
    // Check for built in commands
    if (strcasecmp(inputCommand, "learn command") == 0)
    {
        return true;
    }
    // Check for external commands
    else
    {
        // Get the file path
        char directory[100];
        getFilePath(directory);
        FILE *commandFile;
        commandFile = fopen(directory, "r");

        char command[100];
        while (fscanf(commandFile, fileFormatCommand, command) != EOF)
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
Check if the string is valid for usage
Return true if the string is valid or false if it is not
*/
bool validString(char *inputCommand, bool checkSingleQuote)
{
    // Make sure we didn't just get a newline
    if (strcasecmp("\n", inputCommand) == 0)
    {
        // We just got a newline
        return false;
    }

    // Begin preparation for iteration
    int length = strlen(inputCommand) - 1;
    bool allSpaces = true;
    int arrLocation;

    // Iterate over the string
    for (arrLocation = 0; arrLocation < length; arrLocation++)
    {
        // Check if the character doesn't have a space
        if (inputCommand[arrLocation] != ' ')
        {
            // String has a character other than a space
            allSpaces = false;
        }

        // If the user cares about single quotes and it has them, fail it
        if (checkSingleQuote && inputCommand[arrLocation] == '\'')
        {
            // String contains single quotes when we don't want it to
            return false;
        }

        // Make sure the character isn't our special delimiter
        if (inputCommand[arrLocation] == '\x001F' ||
            inputCommand[arrLocation] == '\x001E')
        {
            // String contains our special delimiter
            return false;
        }
    }

    // Check if it doesn't have just spaces before continuing
    if (allSpaces == true)
    {
        // String is all spaces
        return false;
    }

    // Everything is good to go
    return true;
}

/*
Prepare the string for writing to file
*/
void formatWriteString(char *output, char *command, char *action)
{
    strcat(output, command);
    strcat(output, "\x001F");
    strcat(output, action);
    strcat(output, "\x001E");
}

/*
Get path to the commands file (regular file)
*/
void getFilePath(char *filePath)
{
    strcpy(filePath, getenv("HOME"));
    strcat(filePath, "/.pa/commands");
}

/*
Get path to the commands file (regular file)
*/
void getTempFilePath(char *filePath)
{
    strcpy(filePath, getenv("HOME"));
    strcat(filePath, "/.pa/commands_tmp");
}

/*
################################################################################
Error Message Methods
################################################################################
*/

/*
Tells the user that the command does not exist
*/
void badCommand()
{
    printf("I'm not sure what you mean :(\n");
    exit(1);
}

/*
Tells the user that it could not find the commands file
*/
void fileNotFound()
{
    printf("I can't seem to find my commands :(\n");
    exit(1);
}
