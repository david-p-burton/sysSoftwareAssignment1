#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "transfer.h"
#include "logging.h"


//this updates the website - to be called at appropriate time (night time)

void websiteUpdater()
{

	int x = 0;
	char *command = "cp /home/david/assignment/website/intrasite/* /home/david/assignment/website/live";

	if(system(command) < 0)
	{
		x++;
	}
	else
	{
		x--;
	}
}