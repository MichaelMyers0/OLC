#include "olcr.h"
static olcr_fd;
static fd;
static char buf[buffer_cap];
static answer(buf);
static answer(buf)
char* buf;
{
	ssize_t cnt;
	errno = 0;
	cnt = read(STDIN_FILENO, buf, buffer_cap);
	if (cnt == -1)
	{
		perror("Failed to answer - answer()\n");
		exit(6);
	}
	*(buf + cnt) = 0;
}

olcr_init(port)
int port;
{
	struct sockaddr_in6 s;
	socklen_t slen;
	create_socket(&olcr_fd, AF_INET6, SOCK_STREAM);
	init_sockaddrin_6(&s, port);
	slen = sizeof(s);
	bind_socket(olcr_fd, (const struct sockaddr*)&s, slen);
}

olcr_recieve_question()
{
        ssize_t cnt;
        accept_connection(&fd, olcr_fd, NULL, NULL);
        for (;;)
        {
                errno = 0;
                cnt = read(fd, buf, buffer_cap);
                if (cnt == -1)
                {
                        olcr_reset();
                        exit(3);
                }
                if (cnt || !cnt)
                {
                        *(buf + cnt) = 0;
                        printf("DEBUG_PRINT Question- %s\n", buf);
                        break;
                }
        }
}

olcr_answer()
{
	ssize_t cnt;
	size_t len;
	answer(buf);
	len = strlen(buf);
	for (;;)
	{
		errno = 0;
		cnt = write(fd, buf, len);
		if (cnt == -1)
		{
			perror("olcr_answer() -> failed to answer\n");
			exit(4);
		}
		if (cnt)
			break;
	}
}

olcr_reset()
{
	reuse_port(olcr_fd);
	close_socket(olcr_fd);
	close(fd);
}
