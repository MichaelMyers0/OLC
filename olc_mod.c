#include "olc_mod.h"

olc_ask(buf, len)
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
        *(buf + cnt) = 0;
}

olc_send(fd, msg, num_of_bytes)
int fd;
const char* msg;
int* num_of_bytes;
{
        size_t len;
        len = strlen(msg);
        errno = 0;
        *num_of_bytes = write(fd, msg, len);
}

olc_show(msg)
char* msg;
{

}

