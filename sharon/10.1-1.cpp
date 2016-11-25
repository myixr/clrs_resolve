/*--------2016.11.25----------*
*-introduction to algorithms-*
*-----------10.1-1------------*
*-----------STACK-------------*/

#include <stdio.h>
#include <stdlib.h>

#define N 6

typedef struct{
	int top;
	int data[N];
}Stack;

void Stack_Init(Stack *S);
bool Stack_Empty(Stack *S);
void Stack_Push(Stack *S,int x);
int Stack_Pop(Stack *S);

int main()
{
	Stack *S = (Stack *)malloc(sizeof(Stack));
	int i;

	Stack_Init(S);
	Stack_Push(S,4);
	Stack_Push(S,1);
	Stack_Push(S,3);
	printf("pop stack:%d \n",Stack_Pop(S));
	Stack_Push(S,8);
	printf("pop stack:%d \n",Stack_Pop(S));
	for(i = 0;i < N;i++)
	{
		printf("%d\t",S->data[i]);
	}
	printf("\nStack top is:%d \n",S->top);
	return 0;
}
void Stack_Init(Stack *S)
{	
	int i = 0;
	S->top = -1;
	for(i = 0;i < N;i++)
	{
		S->data[i] = 0;
	}
}
bool Stack_Empty(Stack *S)
{
	if(S->top == -1)
		return true;
	else
		return false;
}
void Stack_Push(Stack *S,int x)
{
	S->top = S->top + 1;
	S->data[S->top] = x;
}
int Stack_Pop(Stack *S)
{
	if(Stack_Empty(S))
	{
		printf("The stack is empty!\n");
	}
	else
	{
		S->top = S->top - 1;
		return S->data[S->top + 1];
	}
		
}
