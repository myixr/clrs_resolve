/*--------2016.12.5----------*
*-introduction to algorithms-*
*-----------10.2-3------------*
*-SINGLY LINKED LIST FOR QUEUE-*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	Node *next;
}ListNode;

typedef struct{
	ListNode *head;
	ListNode * tail;

}ListQueue;
ListQueue *ListQueue_Init();
bool ListQueue_Empty(ListQueue *LQ);
void ListQueue_Enter(ListQueue *LQ,int x);
int ListQueue_Delete(ListQueue *LQ);
void ListQueue_Print(ListQueue *LQ);

int main()
{
	ListQueue *LQ = ListQueue_Init();
	if(LQ == NULL)
	{
		printf("List Queue init failed \n");
		return 0;
	}
	ListQueue_Enter(LQ,4);
	ListQueue_Enter(LQ,1);
	ListQueue_Enter(LQ,3);
	ListQueue_Print(LQ);
	printf("Delete tail:%d \n",ListQueue_Delete(LQ));
	ListQueue_Enter(LQ,8);
	printf("Delete tail:%d \n",ListQueue_Delete(LQ));
	ListQueue_Print(LQ);
	free(LQ);
	return 0;
}
ListQueue *ListQueue_Init()
{
	ListQueue *LQ = (ListQueue *)malloc(sizeof(ListQueue));
	if(LQ == NULL)
	{
		printf("List Queue malloc failed!\n");
		return NULL;
	}else
	{
		Node *tempNode = (Node *)malloc(sizeof(Node));
		LQ->head = tempNode;
		LQ->head->next = NULL;
		LQ->tail = LQ->head;
		return LQ;
	}
}
bool ListQueue_Empty(ListQueue *LQ)
{
	if(LQ->head == LQ->tail)
		return true;
	else
		return false;
}

void ListQueue_Enter(ListQueue *LQ,int x)
{

	Node *tempNode = (Node *)malloc(sizeof(Node));
	if(tempNode == NULL)
	{
		printf("New Node malloc failed!\n");
		return;
	}else
	{
		tempNode->data = x;
		tempNode->next = NULL;
		LQ->tail->next = tempNode;
		LQ->tail = tempNode;

	}
	return;
		
}
int ListQueue_Delete(ListQueue *LQ)
{
	if(ListQueue_Empty(LQ))
	{
		printf("List Queue is empty\n");
		return -1;
	}
	Node *tempNode = LQ->head->next;
	int x = tempNode->data;
	LQ->head->next = tempNode->next;
	if(LQ->tail == tempNode)
	{
		LQ->tail = LQ->head;
	}
	free(tempNode);	
	
	return x;
}
void ListQueue_Print(ListQueue *LQ)
{
	if(ListQueue_Empty(LQ))
	{
		printf("List Queue is empty\n");
		return;
	}
	printf("List Queue elements:\n");
	Node *tempNode = LQ->head->next;
	while( LQ->tail != tempNode)
	{
		printf("%d \t",tempNode->data);
		tempNode = tempNode->next;	
	}
	printf("%d \n",LQ->tail->data);

	return ;
}