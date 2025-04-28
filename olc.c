#include "net.h"

static olc_buf[buffer_cap];

static olc_ask(buf, len);
static olc_send(msg);
static old_show(msg);

static olc_ask(buf, len)
char* buf;
int len;
{
	ssize_t cnt;
	errno = 0;
	cnt = read(STDIN_FILENO, buf, len);
	if (cnt == -1)
	{
		perror("olc_ask()\n");
		exit(1);
	}
}

static olc_send(msg)
const char* msg;	
{

}

static olc_show(msg)
char* msg;
{

}

main()
{
	int fd;
	struct sockaddr_in6 s;
	const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
	socklen_t slen;

	s.sin6_family = AF_INET6;
	s.sin6_port = htons(olc_client1_port);
	s.sin6_addr = in6addr_any;
	slen = sizeof(s);

	create_socket(&fd, AF_INET6, SOCK_STREAM);
	bind_socket(fd, (const struct sockaddr*)&s, slen);
	reuse_port(fd);
	close_socket(fd);

	_exit(0);
}
