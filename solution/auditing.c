#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

#include "date.h"
#include "auditing.h"
#include "messageSender.h"

void auditChecker()
{
	char *temp[200];
	char *date = dateGet(temp);
	char *fileType = ".txt";

	char *command = "ausearch -f /home/david/assignment/website/ > home/david/assignment/logs/logFileAssign";

	if(system(command) < 0)
	{
		messageSender("Operation audit Cancelled");
	}
	else
	{
		messageSender("Audit Checked -  Auditing.c");
	}
}