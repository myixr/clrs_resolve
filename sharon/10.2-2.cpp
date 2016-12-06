/*--------2016.12.5----------*
*-introduction to algorithms-*
*-----------10.2-2------------*
*-SINGLY LINKED LIST FOR STACK-*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	Node *next;
}ListNode;

typedef struct {
	ListNode *top;
}ListStack;

ListStack *ListStack_Init();
bool ListStack_Empty(ListStack *LS);
void ListStack_Push(ListStack *LS,int x);
int ListStack_Pop(ListStack *LS);
void ListStack_Print(ListStack *LS);
int main()
{
	ListStack *LS = ListStack_Init();
	if(LS == NULL)
	{
		printf("Init ListStack error!\n");
		return 0;
	}
	ListStack_Push(LS,4);
	ListStack_Push(LS,1);
	ListStack_Push(LS,3);
	ListStack_Print(LS);
	printf("pop stack:%d \n",ListStack_Pop(LS));
	ListStack_Push(LS,8);
	ListStack_Print(LS);
	printf("pop stack:%d \n",ListStack_Pop(LS));
	ListStack_Print(LS);
	free(LS);
	
	return 0;
}
ListStack *ListStack_Init()
{	
	ListStack *LS = (ListStack *)malloc(sizeof(ListStack));
	if(LS == NULL)
	{
		printf("ListStack malloc error!\n");
		return NULL;
	}else
	{
		LS ->top = NULL;	
	}
	return LS;
}
bool ListStack_Empty(ListStack *LS)
{
	if(LS->top == NULL)
		return true;
	else
		return false;
}
void ListStack_Push(ListStack *LS,int x)
{
	Node *tempNode = (Node *)malloc(sizeof(Node));
	if(tempNode == NULL)
	{
		printf("New Node malloc failed!\n");
		return;
	}else
	{
		tempNode->data = x;
		tempNode->next = LS->top;
		LS->top = tempNode;
	}
	return;
}
int ListStack_Pop(ListStack *LS)
{
	if(ListStack_Empty(LS))
	{
		printf("The ListStack is empty!\n");
		return -1;
	}
	else
	{
		Node *tempNode = LS->top;
		LS->top = LS->top->next;
		int topElem = tempNode->data;
		free(tempNode); 
		return topElem;
	}
		
}
void ListStack_Print(ListStack *LS)
{
	if(ListStack_Empty(LS))
	{
		printf("The ListStack is empty!\n");
	}
	else
	{
		Node *tempNode = LS->top;
		printf("print list stack elements from top to bottom:\n");
		while(tempNode->next != NULL)
		{
			printf("%d \t",tempNode->data);
			tempNode = tempNode->next;
		}
		printf("%d\n",tempNode->data);
	}
}
