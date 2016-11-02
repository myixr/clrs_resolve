/*--------2016.11.2----------*
*-introduction to algorithms-*
*-----------6.2-1------------*
*--------MAX-HEAPIFY---------*/

#include <stdio.h>
#include <stdlib.h>

void Max_HeapIfy(int *array,int size,int i);

int main()
{
	int array[] = {27,17,3,16,13,10,1,5,7,12,4,8,9,0};
	int size = 14;
	int i;	
	Max_HeapIfy(array,size,2);//与数组下标相一致 
	printf("After Max_HeapIfy:");
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