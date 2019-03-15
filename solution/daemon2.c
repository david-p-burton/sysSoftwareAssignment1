//Orphan Example
//The child process is adopted by init process, when parent processes die
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "time.h"

int main()
{
	pid_t pid, sid;
	int x;
	pid = fork();

	
	if(0 != mkdir("home/david/some/directory", 0700))
	{
		printf("error");
		perror("mkdir");
	}

	if(pid > 0) // anything other than 0 is the parent process
	{
		printf("This is a PARENT process! PID is; %d\n", pid);
		exit(EXIT_SUCCESS); //kills the parent
	}
	if (pid < 0)
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
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);

	for(x = sysconf(_SC_OPEN_MAX); x >=0; x--)
	{
		close(x);
	}

	//daemon specific initialization here

	while(1)
	{
		//do some task
		sleep(30);


		mkdir("home/david//some/directory2", 0700);
		
	}
}