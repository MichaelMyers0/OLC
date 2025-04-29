#include "queue.h"

qinit(q)
queue_t* q;
{
	q->fornt = -1;
	q->rear = -1;
}

qputs(q, s)
queue_t* q;
const char* s;
{
	size_t len;
	(q->rear)++;
	if (q->rear == q->front)
	{
		fprintf(stderr, "ERROR: queue is full\n");
		return -1;
	}
	len = strlen(s);
	if (len >= capacity)
	{
		fprintf(stderr, "ERROR: string is too long\n");
		return -2;
	}
	strcpy(q->q + q->rear, s); 
	*(q->q + q->rear + len) = 0;
}
