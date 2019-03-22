#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>

#include "permissions.h"
#include "messageSender.h"

void lockFiles()
{
	int status;
	int i = strtol("1111", 0, 8);
	char dirAddress[200] = "home/david/assignment/website/";

	if(chmod(dirAddress, i) < 0)
	{
		messageSender("No permissions changed! (locking)\n");
	}
	
}

void unlockFiles()
{
	int status;
	int i = strtol("0777", 0, 8);
	char dirAddress[200] = "home/david/assignment/website/";

	if(chmod(dirAddress, i) < 0)
	{
		messageSender("No permissions changed! (unlocking)\n");
	}
	
}