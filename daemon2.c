//Orphan Example
//The child process is adopted by init process, when parent processes die
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	pid_t pid, sid;
	pid = fork();
	
	if(pid > 0) // anything other than 0 is the parent process
	{
		printf("This is a PARENT process!\n");
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
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	//daemon specific initialization here

	while(1)
	{
		//do some task
		sleep(30);
		
	}
}