#include "net.h"
create_socket(fd, domain, type)
int* fd;
int domain;
int type;
{
	errno = 0;
	*fd = socket(domain, type, 0);
	if (*fd == -1)
	{
		perror("create_socket()->socket()\n");
		exit(1);
	}
}
bind_socket(fd, addr, slen)
int fd;
const struct sockaddr* addr;
socklen_t slen;
{
	int res;
	errno = 0;
	res = bind(fd, addr, slen);
	if (res == -1)
	{
		perror("bind_socket()->bind()");
		exit(2);
	}
}
connect_to_a_server(fd, addr, slen)
int fd;
const struct sockaddr* addr;
socklen_t slen;
{
	int res;
	errno = 0;
	res = connect(fd, addr, slen);
	if (res == -1)
	{
		perror("connect_to_a_server()->connect()\n");
		exit(3);
	}
}
accept_connection(fd, sfd, addr, slen)
int* fd;
int sfd;
struct sockaddr* addr;
socklen_t* slen;
{
	errno = 0;
	*fd = accept(sfd, addr, slen);
	if (*fd == -1)
	{
		perror("accept_connection()\n");
		exit(4);
	}
}
reuse_port(fd)
int fd;
{
	int n = 1, res;
        errno = 0;
        res = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));
        if (res == -1)
        {
                perror("setsockopt()\n");
                exit(5);
        }	
}
close_socket(fd)
int fd;
{
	int res;
        errno = 0;
        res = close(fd);
        if (res == -1)
        {
                perror("close_socket()->close()\n");
                exit(6);
        }	
}
make_socket_listening(fd, log)
int fd;
int log;
{
	int res;
	errno = 0;
	res = listen(fd, log);
	if (res == -1)
	{
		perror("make_socket_listening()->listen()\n");
		exit(7);
	}
}
