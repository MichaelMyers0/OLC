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
	create_socket(&fd, AF_INET6, SOCK_STREAM);
	close_socket(fd);
	_exit(0);
}
