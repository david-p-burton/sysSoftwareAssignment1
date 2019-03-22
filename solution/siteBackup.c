#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "date.h"
#include "messageSender.h"

void createBackup()
{

	//copy command - this command copies over files and creates directories if they are not already there
	char *command = "sudo rsync -avzh /home/david/assignment/website/intrasite /home/david/assignment/backup/";
	

	char name[200];

	char *folderName = dateGet(name);
	
	int totalLength = strlen(command) + strlen(folderName) + 1; // +1 for null terminator
	
	char *finalCommand = (char *)malloc(totalLength);

	strcpy(finalCommand, command);
	strcat(finalCommand, folderName);


	if(system(finalCommand) < 0)
	{
		messageSender("Could not create backup.");
	}
	else
	{
		messageSender("Backup of website created!");
	}

	free(finalCommand);
}