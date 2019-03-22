#include <stdio.h>
#include <time.h>

#include "date.h"

char* dateGet(char *buffer)
{

	time_t rawtime;
	struct tm *info;

	time(&rawtime);

	info = localtime(&rawtime);

	strftime(buffer, 100, "%Y-%m-%d_%I:%M:%S%p", info);
	return buffer;

}