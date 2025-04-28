#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <syslog.h>
#define NUM_OF_DESCRIPTORS 3
#define SLEEP_T 30
#define NUM_OF_CYCLES 10000
static close_descriptors();
static open_descriptors();
static close_descriptors()
{
	int i;
	for (i = 0; i < NUM_OF_DESCRIPTORS; i++)
		close(i);
}
static open_descriptors()
{
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_WRONLY);
	open("/dev/null", O_WRONLY);
}
main()
{
	pid_t child, sid;
	int i;
	close_descriptors();
	open_descriptors();
	openlog("main.c", LOG_PID, LOG_USER);
	errno = 0;
	child = fork();
	if (child == -1)
	{
		syslog(LOG_ERR, "ERROR: Failed to create a process\n");
		_exit(1);
	}
	if (child == 0)
	{
		errno = 0;
		sid = setsid();
		if (sid == -1)
		{
			syslog(LOG_ERR, "ERROR: Failed to start a new session\n");
			_exit(2);
		}
		errno = 0;
		child = fork();
		if (child == -1)
		{
			syslog(LOG_ERR, "ERROR: Child failed to create a process\n");
			_exit(3);
		}
		if (child == 0)
		{
			for (i = 0; i < NUM_OF_CYCLES; i++)
			{
				(LOG_INFO, "Infinite loop\n");
				sleep(SLEEP_T);
			}
			closelog();
			_exit(0);
		}
		else
		{
			syslog(LOG_INFO, "Child process was terminated\n");
			_exit(0);
		}
	}
	else
	{
		syslog(LOG_INFO, "Parent process was finished\n");
		_exit(0);
	}
}
