#include "date.h"
#include <stdio.h>
#include <time.h>

char* dateGet(char * buffer)
{

	time_t rawtime;
	struct tm *info;

	time(&rawtime);

	info = localtime(&rawtime);

	strftime(buffer, 100, "%c", info);

	return buffer;



}