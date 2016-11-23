/*--------2016.11.23----------*
*-introduction to algorithms-*
*-----------9.3-8------------*
*-----MEDIAN TWO ARRAY------*/

#include <stdio.h>
#include <stdlib.h>

int Median_TwoArray(int *arrayA,int *arrayB,int size);
int Median_find(int *arrayA,int *arrayB,int size,int l,int h);
int main()
{
	int arrayA[] = {2,4,7,8,9,10,14,15,17,18};
	int arrayB[] = {1,3,5,6,11,12,13,16,19,20};
	int size = 10;
		 	
	int m = Median_TwoArray(arrayA,arrayB,size);
	printf("median of two array is :%d\n",m);
	
	return 0;
}
int Median_find(int *arrayA,int *arrayB,int size,int l,int h)
{
	int k;
	if (l > h)
	{
		return NULL;
	}
	else (k = (int)((l + h)/2));
	if(k == size && arrayA[size - 1] <= arrayB[0])
	{
		return arrayA[size - 1];
	}
	else if(k < size && (arrayB[size-2 - k] <= arrayA[k])&&(arrayA[k] <= arrayB[size-2-k+1]))
	{
		return arrayA[k];
	}
	else if(arrayA[k] > arrayB[size-2 -k+1])
	{
		return Median_find(arrayA,arrayB,size,l,k - 1);
	}
	else 
		return Median_find(arrayA,arrayB,size,k + 1,h);
}
int Median_TwoArray(int *arrayA,int *arrayB,int size)
{
	int median = Median_find(arrayA,arrayB,size,0,size - 1);
	if(median == NULL)
	{
		median = Median_find(arrayB,arrayA,size,0,size - 1);
	}
	return median;
}