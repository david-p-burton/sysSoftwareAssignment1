//The child process is adopted by init process, when parent processes die
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

//custom headers files
#include "date.h"
#include "transfer.h"
#include "siteBackup.h"
#include "permissions.h"
#include "auditing.h"

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

	char *command = "auditctl -w /home/david/assignment/website/intrasite -p rwxa";

	if(system(command) < 0)
	{
		openlog("TestLog", LOG_PID | LOG_CONS, LOG_USER);
		syslog(LOG_INFO, "Could not begin auditing\nSomething went wrong or the developer is a dunce!\n%s", strerror(errno));
		closelog();
	}
	else
	{
		system("echo woot!");
	}

	//outlined above - essentially just creates out daemon
	summonADaemon();

	while(1)
	{
		sleep(30);
		int fileDescriptor;
		char *queueFile = "home/david/assignment/logs/logFileAssign";
		char buffer[1024] = "";
		fileDescriptor = open(queueFile, O_RDONLY);

		read(fileDescriptor, buffer, 1024);
		

		//standard daily backup and go live
		if(1)
		{
			lockFiles();
			createBackup();
			websiteUpdater();
			unlockFiles();
		}

		//backup EMERGENCY call
		if(strcmp(buffer, "1") == 0)
		{
			lockFiles();
			createBackup();
			unlockFiles();
		}

		close(fileDescriptor);

		//update EMERGENCY call
		if(strcmp(buffer, "2") == 0)
		{
			lockFiles();
			websiteUpdater();
			unlockFiles();
		}

		auditChecker();
	}

	return 0;
}