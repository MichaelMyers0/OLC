#include "olcd.h"
static queue_t q;
static char olcd_buf[buffer_cap];
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
	struct sockaddr_in6 s, dst;
	socklen_t slen;
	ssize_t cnt;

	qinit(&q);
#if 0	
	close_descriptors();
	open_descriptors();
#endif	
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
			create_socket(&fd, AF_INET6, SOCK_STREAM);
			init_sockaddrin_6(&s, olcd_port);
			slen = sizeof(s);
			bind_socket(fd, (const struct sockaddr*)&s, slen);
			make_socket_listening(fd, log);
			accept_connection(&ffd, fd, (struct sockaddr*)&dst, &slen);
#if 0			
			for (;;)
#else
			i = 0;	
			while (i < num_of_clients_to_server - 3)	
#endif				
			{
				errno = 0;
				cnt = read(ffd, olcd_buf, buffer_cap);
				if (cnt == -1)
				{
					syslog(LOG_ERR, "ERROR: olcd failed to recieve a message");
					break;
				}
#if 0				
				if (cnt == 0)
					break;
#endif				
				if (cnt)
				{
					*(olcd_buf + cnt) = 0;
#if 1
					printf("MESSAGE - %s\n", olcd_buf);
#endif					
					qputs(&q, olcd_buf);
					*olcd_buf = 0;
					syslog(LOG_INFO, "olcd recieve a message from a client\n");
					i++;
					printf("DEBUG_PRINT - %d\n", i);
#if 0					
					break;
#endif					
				}

			}
			reuse_port(fd);
			close_socket(fd);
			close(ffd);
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
