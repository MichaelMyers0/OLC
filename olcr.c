#include "olcr.h"
static olcr_fd;
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

}

olcr_answer()
{

}

olcr_reset()
{
	reuse_port(olcr_fd);
	close_socket(olcr_fd);
}
