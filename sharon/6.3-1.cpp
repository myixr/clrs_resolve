/*--------2016.11.2----------*
*-introduction to algorithms-*
*-----------6.2-1------------*
*------BUILD_MAX-HEAPIFY-----*/

#include <stdio.h>
#include <stdlib.h>

void Max_HeapIfy(int *array,int size,int i);
void Build_Max_HeapIfy(int *array,int size);
int main()
{
	int array[] = {5,3,17,10,84,19,6,22,9};
	int size = 9;
	int i;	
	Build_Max_HeapIfy(array,size);
	printf("After Build_Max_HeapIfy:");
 	for(i = 0;i < size;i++)
 	{
		printf("%d,",array[i]); 	
 	}
	return 0;
}
void Max_HeapIfy(int *array,int size,int i)
{
	int largest,temp;
	int l = 2*i + 1;
	int r = 2*i + 2;
	if((l < size) && (array[l] > array[i]))
	{
		largest = l;	
	}
	else
	{
		largest = i;
	}
	if((r < size) && (array[r] > array[largest]))
	{
		largest = r;
	}
	if(largest != i)
	{
		temp = array[i];
		array[i] = array[largest];
		array[largest] = temp;
		Max_HeapIfy(array,size,largest);
	}	
}
void Build_Max_HeapIfy(int *array,int size)
{
	int i;
	for(i = size/2 - 1;i >=0;i--)
	{
		Max_HeapIfy(array,size,i);
	}
}