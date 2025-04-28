#include "olcd.h"
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
run_olc_daemon()
{
	pid_t child, sid;
	int i, fd, ffd;
	struct sockaddr_in6 s;
	socklen_t slen;

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
#if 1
			create_socket(&fd, AF_INET6, SOCK_STREAM);
			init_sockaddrin_6(&s, olcd_port);
			slen = sizeof(s);
			bind_socket(fd, (const struct sockaddr*)&s, slen);
			make_socket_listening(fd, log);
			accept_connection(&ffd, fd, NULL, NULL);			/*later provide structure to get an addr*/
#endif			
			for (i = 0; i < NUM_OF_CYCLES; i++)
			{
				syslog(LOG_INFO, "Infinite loop\n");
				sleep(SLEEP_T);
			}
#if 1
			reuse_port(fd);
			close_socket(fd);
			close(ffd);
#endif
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
