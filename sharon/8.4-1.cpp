/*--------2016.11.16----------*
*-introduction to algorithms-*
*-----------8.4-1------------*
*--------BUCKET SORT---------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct list_node{
	float data;
	struct list_node* next;
}list_node;

void List_init(list_node *list);
void List_Insert(list_node *list,float data);
void List_sort(list_node *list);
void Bucket_sort(float *arrayA,int size,int bucket_size);

int main()
{
	float A[10] = {0.79,0.13,0.16,0.64,0.39,0.20,0.89,0.53,0.71,0.42};
	int size = 10;
	int bucket_size  = 10;

	int i;
	Bucket_sort(A,size,bucket_size);
	printf("After Bucket_sort:\n");
	for(i = 0;i < size;i++)
	{
		printf("%0.2f\n",A[i]);
	}	
	return 0;
}
void List_init(list_node *list)
{
	list->data = 0;
	list->next = NULL;
}
void List_append(list_node *list,float data)
{
	list_node *TempNode = (list_node *)malloc(sizeof(list_node));
	list_node *Node = list;
	TempNode->data = data;
	TempNode->next = NULL;
	while(Node->next != NULL)
	{
		Node = Node->next;
	}
	Node->next = TempNode;
}
void List_sort(list_node *list)
{	
 	list_node *first;  
    list_node *t;  
    list_node *p;  
    list_node *q;  
  
    first = list->next;
    list->next = NULL; 
  
    while (first != NULL) 
    {  
       
        for(t = first, q = list; ((q != NULL) && (q->data < t->data)); p = q, q = q->next); 
  
        first = first->next; 
    
        if (q == list) 
        {  
            list = t;  
        }  
        else 
        {  
            p->next = t;  
        }  
        t->next = q; 
    } 
	
}
void Bucket_sort(float *arrayA,int size,int bucket_size)
{
	int i,j,temp;
	list_node *TempNode = (list_node *)malloc(sizeof(list_node));
 	list_node **Buckets = (list_node **)malloc(bucket_size *sizeof(list_node *));
	for(i = 0;i < bucket_size;i++)
	{	
		Buckets[i] = (list_node *)malloc(sizeof(list_node));
		List_init(Buckets[i]);
	}
	for(i = 0;i < size;i++)
	{	
		temp = floor(bucket_size * arrayA[i]);
		
	 	List_append(Buckets[temp],arrayA[i]);
	}

	j = 0;
	for(i = 0;i < bucket_size;i++)
	{
		List_sort(Buckets[i]);
		for(TempNode = Buckets[i]->next;TempNode != NULL;TempNode = TempNode->next)
		{
			printf("TempNode->data:%f\n",TempNode->data);
			arrayA[j++] = TempNode->data;
		}
	}
	free(TempNode);
	for(i = 0;i < bucket_size; i++)
	{
		free(Buckets[i]);
	}
	free(Buckets);
}