#include <stdio.h>
#include <time.h>

#include "date.h"

char* dateGet(char *buffer)
{

	time_t tempTime;
	struct tm *returnTime;

	time(&tempTime);

	returnTime = localtime(&tempTime);

	strftime(buffer, 100, "%Y-%m-%d_%I:%M:%S%p", returnTime);
	return buffer;

}