#include <stdio.h>
#include <unistd.h>
#include <syslog.h>

void writeMessageToSyslog(const char* message)
{
	openlog("Test", LOG_CONS, LOG_USER);
	syslog(LOG_ERR, "%s", message);
	closelog();
}