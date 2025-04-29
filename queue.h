#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
enum {capacity = 1024};
typedef char string_t[capacity];
typedef struct
{
	string_t q[capacity];
	int front;
	int rear;
}queue_t;
qinit(q);
qputs(q, s);
qgets();
#endif
