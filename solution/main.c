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
#include "messageSender.h"

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

	//time variables to be used for scheduling backups etc.

	//took me a while to figure out that daylights savings time plays a big part in this
	//the local time is return a time that is 1 hour ahead!!!
	//I should put this up on stackoverflow somewhere in case I'm not the only one who missed this
	int timeCheck = 0;
	struct tm time1 = {0};
	struct tm *time2;
	time_t realTime;
	time(&realTime);

	//Time for out automatic backups
	time1.tm_hour = 00;
	time1.tm_min = 7;
	time1.tm_sec = 0;
	time1.tm_mday = 23;
	time1.tm_mon = 2;
	time1.tm_year = 119;

	time2 = localtime(&realTime);

	time_t TimeUse1 = mktime(&time1);
	time_t TimeUse2 = mktime(time2);


	//set audit on intrasite to see changes
	char *command = "auditctl -w /home/david/assignment/website/intrasite -p rwxa";

	//execute above command - sys log if there is an error
	if(system(command) < 0)
	{
		openlog("TestLog", LOG_PID | LOG_CONS, LOG_USER);
		syslog(LOG_INFO, "Could not begin auditing\nSomething went wrong or the developer is a dunce!\n%s", strerror(errno));
		closelog();
	}
	else
	{
		//audit successfully created
		system("echo woot!");
	}

	//outlined above - essentially just creates out daemon
	summonADaemon();

	//daemon loop
	while(1)
	{
		sleep(1);
		//time checking for daily backup
		time(&realTime);
		time2 = localtime(&realTime);

		time_t TimeUse2 = mktime(time2);

		timeCheck = TimeUse2 - TimeUse1;


		int emergencyOperation;
		char *queueFile = "home/david/assignment/logs/EMERGENCYFILECALL";
		char buffer[1024] = "";
		emergencyOperation = open(queueFile, O_RDONLY);

		read(emergencyOperation, buffer, 1024);
		

		//standard daily backup and go live
		if(timeCheck == 0)
		{

			messageSender("Performing Daily Processes");
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

		close(emergencyOperation);

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