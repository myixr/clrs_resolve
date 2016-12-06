/*--------2016.12.6----------*
*-introduction to algorithms-*
*-----------10.2-7------------*
*---SINGLY LINKED REVERSAL----*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	Node *next;
}ListNode;
typedef struct{
	ListNode *next;
}ListHead;

ListHead *List_Init();
ListHead *List_Reversal(ListHead *head);
void List_Print(ListHead *head);
int main()
{
	ListHead *head = List_Init();
	if(head == NULL)
	{
		printf("Init List failed!\n");
	}
	int i ;
	ListNode *tempNode[10];
	for(i = 0;i<10;i++)
	{
		tempNode[i] = (ListNode *)malloc(sizeof(ListNode));
		tempNode[i]->data = i;
		tempNode[i]->next = NULL;
		if(i ==0 )
		{
			head->next = tempNode[i];
		} 
		else
		{
			tempNode[i - 1]->next = tempNode[i];
		}
	}

	printf("Before reversal:\n");
	List_Print(head);
	
	head = List_Reversal(head);
	printf("After Reversal:\n");
	List_Print(head);
	
	free(head);
	return 0;
}
ListHead *List_Init()
{
	ListHead *head = (ListHead *)malloc(sizeof(ListHead));
	if(head == NULL)
	{
		printf("malloc for List head failed!\n");
		return NULL;
	}
	head->next = NULL;
	return head;	
}

ListHead *List_Reversal(ListHead *head)
{
	ListNode *temp1 = head->next;
	ListNode *temp2 = NULL;
	ListNode *end = head->next;
	
	while(end->next != NULL)
	{
		end = end->next;
	}
	while(temp1 != end)
	{
		head->next = temp1->next;
		end->next = temp1;
		if(temp2 == NULL)
		{
			temp1->next = NULL;
		}
		else
		{
			temp1->next = temp2;
		}
		temp2 = temp1;
		temp1 = head->next;
	}
	return head;
}
void List_Print(ListHead *head)
{	
	ListNode *tempNode2 = head->next;
	while(tempNode2->next != NULL)
	{
		printf("%d\t",tempNode2->data);
		tempNode2 = tempNode2->next;		
	}
	printf("%d\n",tempNode2->data);
	return ;
}