/*--------2016.11.25----------*
*-introduction to algorithms-*
*-----------10.1-1------------*
*-----------QUEUE-------------*/

#include <stdio.h>
#include <stdlib.h>

#define N 6

typedef struct{
	int head;
	int tail;
	int data[N];
}Queue;
void Queue_Init(Queue *Q);
bool Queue_Empty(Queue *Q);
bool Queue_Full(Queue *Q);
void Queue_Enter(Queue *Q,int x);
int Queue_Delete(Queue *Q);


int main()
{
	Queue *Q = (Queue *)malloc(sizeof(Queue));
	int i;

	Queue_Init(Q);
	Queue_Enter(Q,4);
	Queue_Enter(Q,1);
	Queue_Enter(Q,3);
	printf("Delete tail:%d \n",Queue_Delete(Q));
	Queue_Enter(Q,8);
	printf("Delete tail:%d \n",Queue_Delete(Q));
	for(i = 0;i < N;i++)
	{
		printf("%d\t",Q->data[i]);
	}
	printf("\nQueue head is:%d  tail is:%d\n",Q->head,Q->tail);
	return 0;
}
void Queue_Init(Queue *Q)
{
	int i;
	Q->head = 0;
	Q->tail = 0;
	for(i = 0;i < N;i++)
	{
		Q->data[i] = 0;
	}
}
bool Queue_Empty(Queue *Q)
{
	if(Q->head == Q->tail)
		return true;
	else
		return false;
}
bool Queue_Full(Queue *Q)
{
	if(Q->head == (Q->tail + 1))
		return true;
	else
		return false;
}
void Queue_Enter(Queue *Q,int x)
{
	Q->data[Q->tail] = x;
	if(Q->tail == N - 1)
		Q->tail = 0;
	else
		Q->tail = Q->tail + 1;
		
}
int Queue_Delete(Queue *Q)
{
	int x;
	x = Q->data[Q->head];
	if(Q->head == N - 1)
		Q->head = 0;
	else
		Q->head = Q->head + 1;
		
	return x;
}