#include "net.h"
#include "olc_mod.h"
enum {olc_client2_port = 5006};
#if 0
static olc_show(msg)
char* msg;
{

}
#endif

static char olc_buf[buffer_cap];

main()
{
	int fd, num_of_bytes;
	struct sockaddr_in6 s, sd;
	const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
	socklen_t slen, sdlen;
	ssize_t cnt;

	init_sockaddrin_6(&s, olc_client2_port);
	slen = sizeof(s);
	init_sockaddrin_6(&sd, olcd_port);
	sdlen = sizeof(sd);

	create_socket(&fd, AF_INET6, SOCK_STREAM);
	bind_socket(fd, (const struct sockaddr*)&s, slen);
	connect_to_a_server(fd, (const struct sockaddr*)&sd, sdlen);
	sleep(sleep_t);
	olc_ask(olc_buf, buffer_cap);
	for (;;)
	{
		olc_send(fd, olc_buf, &num_of_bytes);
		if (num_of_bytes)
			break;
		if (num_of_bytes == -1)
		{
			fprintf(stderr, "ERROR: Failed to send a message to the olcd daemon\n");
			break;
		}
	}
	reuse_port(fd);
	close_socket(fd);

	_exit(0);
}
