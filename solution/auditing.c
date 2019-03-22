#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "date.h"
#include "messageSender.h"

void setAuditWatch()
{
	char *temp[200];
	char *date = dateGet(temp);
	char *fileType = ".txt";

	char *command = "auditctl -w /home/david/assignment/website/intrasite -p rwxa";
}