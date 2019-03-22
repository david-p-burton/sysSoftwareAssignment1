#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>

#include "transfer.h"
#include "logging.h"
#include "messageSender.h"


//this updates the website - to be called at appropriate time (night time)

void websiteUpdater()
{

	int x = 0;
	char *command = "cp /home/david/assignment/website/intrasite/* /home/david/assignment/website/live";

	if(system(command) < 0)
	{
		messageSender("Could not update website!");

		openlog("Test", LOG_PID, LOG_USER);
		syslog(LOG_INFO, "copy failed");
		closelog();
	}
	else
	{
		messageSender("Website updated!");
	}
}