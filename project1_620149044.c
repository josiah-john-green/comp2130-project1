#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>

int main()
{

	FILE *fptr;

	char filename[] = "keylogfile.txt";

	char kpinput;

	char commandBuffer[100];

	char currentDir[256];

    int commandExecuted = 0;

    fptr = fopen(filename, "a+");

	if (fptr == NULL)
    {

	    printf("Unable to open the file.\n");

	    return 1;

	}
	else
	{

		_getcwd(currentDir, 256);

        printf("\n%s> ", currentDir);

        while (1)
		{

		    kpinput = fgetc(stdin);

            if (kpinput == '~')
			{

		        break;

		    }
            else if (kpinput == '\n')
            {

                if (strncmp("exit", commandBuffer, 4) == 0)
                {

                    break;

                }
                else if (strncmp("cd", commandBuffer, 2) == 0)
                {

                    // Extract the directory path from the command

                    char *newPath = &commandBuffer[3]; // Assumes "cd " is used

                    if (_chdir(newPath) == 0)
                    {

                        // Directory change successful

                        _getcwd(currentDir, 256); // Update the current directory

                        printf("\n%s> ", currentDir);

                    }
                    else
                    {

                        printf("\nDirectory not found.");

                        break;

                    }

                }
                else if (strncmp("run_program", commandBuffer, 11) == 0)
                {

                    if (!commandExecuted)
                    {

                        // Extract the program name from the command

                        char *programName = &commandBuffer[12]; // Assumes "run_program " is used

                        printf("\nRunning the program: %s", programName);

                        system(programName); // Run the specified program

                        commandExecuted = 1; // Set the flag to indicate command execution

                        printf("\n%s> ", currentDir);

                    }

                }
                else
                {

                    if (!commandExecuted) {

                        // Execute system utilities via cmd.exe

                        char systemCommand[200]; // Maximum command length

                        snprintf(systemCommand, sizeof(systemCommand), "cmd.exe /c %s", commandBuffer);

                        printf("\nExecuting system command: %s", systemCommand);

                        system(systemCommand);

                        commandExecuted = 1;

                        printf("\n%s> ", currentDir);

                    }

                }

                memset(commandBuffer, 0, sizeof(commandBuffer));

                commandExecuted = 0; // Reset the flag for the next command

            }
			else
			{

			    strncat(commandBuffer, &kpinput, 1);

			}
			fputc(kpinput, fptr);


		}


	}
    fclose(fptr);

	return 0;

}
