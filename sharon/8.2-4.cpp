/*--------2016.11.16----------*
*-introduction to algorithms-*
*-----------8.2-4------------*
*-----COUNTING SORT8.2-4-----*/

#include <stdio.h>
#include <stdlib.h>

void Counting_C(const int *arrayA,int *arrayC,int n,int k);
int Counting(int *arrayC,int a,int b);

int main()
{
	int arrayA[] = {2,5,3,0,2,3,0,3}; 
	int size = 8;
	int k = 5;
	int a = 1;
	int b = 5;
	int count;
	int *arrayC = (int *)malloc((k + 1) * sizeof(int));
	Counting_C(arrayA,arrayC,size,k);
	count = Counting(arrayC,a,b);
	printf("There are %d numbers between a:%d and b:%d(include a and b)\n ",count,a,b);	
	return 0;
}

void Counting_C(const int *arrayA,int *arrayC,int n,int k)
{
	int i;
	for(i = 0;i <= k;i++)
	{
		arrayC[i] = 0;
	}
	for(i = 0;i < n;i++)
	{
		arrayC[arrayA[i]] = arrayC[arrayA[i]] + 1;
	}
	for(i = 1;i <= k;i++ )
	{
		arrayC[i] = arrayC[i] + arrayC[i - 1];
	}
	return;
}
int Counting(int *arrayC,int a,int b)
{
	return arrayC[b] - arrayC[a - 1];
}