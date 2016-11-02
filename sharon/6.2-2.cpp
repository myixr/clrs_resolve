/*--------2016.11.2----------*
*-introduction to algorithms-*
*-----------6.2-2------------*
*--------MIN-HEAPIFY---------*/

#include <stdio.h>
#include <stdlib.h>

void Min_HeapIfy(int *array,int size,int i);

int main()
{
	int array[] = {27,17,16,13,12,10,9,8,7,5,4,3,1,0};
	int size = 14;
	int i;	
	Min_HeapIfy(array,size,0);//与数组下标相一致 
	printf("After Max_HeapIfy:");
 	for(i = 0;i < size;i++)
 	{
		printf("%d,",array[i]); 	
 	}
	return 0;
}
void Min_HeapIfy(int *array,int size,int i)
{
	int minmum,temp;
	int l = 2*i + 1;
	int r = 2*i + 2;
	if((l < size) && (array[l] < array[i]))
	{
		minmum = l;	
	}
	else
	{
		minmum = i;
	}
	if((r < size) && (array[r] < array[minmum]))
	{
		minmum = r;
	}
	if(minmum != i)
	{
		temp = array[i];
		array[i] = array[minmum];
		array[minmum] = temp;
		Min_HeapIfy(array,size,minmum);
	}	
}