//The child process is adopted by init process, when parent processes die
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

//custom headers files
#include "time.h"
#include "transfer.h"

static void summonADaemon()
{
	pid_t pid, sid;
	int fileDescriptors;

	pid = fork();

	// anything other than 0 is the parent process
	if(pid > 0) 
	{
		//kills the parent
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		// log failure
		exit(EXIT_FAILURE);
	}
	
	//give daemon read and write permissions
	umask(0);

	//new SID for child process for when it becomes a daemon
	sid = setsid();
	if(sid < 0)
	{
		exit(EXIT_FAILURE);
	}

	//changes current working directory to root
	if((chdir("/")) < 0)
	{
		exit(EXIT_FAILURE);
	}

	//close std file descriptors
	for(fileDescriptors = sysconf(_SC_OPEN_MAX); fileDescriptors >=0; fileDescriptors--)
	{
		close(fileDescriptors);
	}

	openlog("daemonBasic", LOG_PID, LOG_DAEMON);

}

int main(int argc, char *argv[])
{
	summonADaemon();
}