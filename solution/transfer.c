#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "transfer.h"
#include "logging.h"

void websiteUpdater()
{

	int x = 0;
	// char *path = "rsync -r /home/david/assignment/website/intrasite/* /home/david/assignment/website/live";
	char *path = "cp /home/david/assignment/website/intrasite/* /home/david/assignment/website/live";

	if(system(path) < 0)
	{
		x++;
	}
	else
	{
		x--;
	}
}