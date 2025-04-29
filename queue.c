#include "queue.h"

qinit(q)
queue_t* q;
{
	q->front = -1;
	q->rear = -1;
}

qputs(q, s)
queue_t* q;
const char* s;
{
	int len;
	if (q->rear == capacity)
		q->rear = 0;
	else
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
	strcpy(q->q[q->rear], s); 
	q->q[q->rear][len] = 0;
}

qgets(q, p)
queue_t* q;
pointer_t** p;
{
	if (q->front == capacity)
		q->front = 0;
	else
		(q->front)++;
	if (q->front == q->rear)
	{
		fprintf(stderr, "ERROR: queue is empty\n");
		return -3;
	}
	*p = q->q[q->front];
}

