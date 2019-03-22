#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "date.h"

void createBackup()
{

	//copy command
	char *command = "rsync -avzh /home/david/assignment/website/intrasite /home/david/assignment/backup/";
	char name[200];
	char *folderName = dateGet(name);
	int totalLength = strlen(command) + strlen(folderName) + 1; // +1 for null terminator
	char *finalCommand = (char *)malloc(totalLength);

	strcpy(finalCommand, command);
	strcat(finalCommand, folderName);

	printf("%s", finalCommand);

	int x=0;


	if(system(finalCommand) < 0)
	{
		x++;
	}
	else
	{
		x--;
	}

	free(finalCommand);
}