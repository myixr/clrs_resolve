/*--------2016.11.4----------*
*-introduction to algorithms-*
*-----------6.5-3------------*
*-MIN HEAP FOR MIN PRIORITY QUEUE-*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void Min_HeapIfy(int *array,int size,int i);
void Build_Min_Heap(int *array,int size);
int Heap_Minimum(int *array,int size);
int Heap_Extract_Min(int *array,int size);
void Heap_Decrease_Key(int *array,int i,int key);
void Min_Heap_Insert(int *array,int key,int size);
int main()
{
	int array[] = {27,17,16,13,12,10,9,8,7,5,4,3,1,0};
	int size = 14;
	int i;
	int key = 11;		
	Build_Min_Heap(array,size);//与数组下标相一致 

 	printf("\nThe minmum element is:%d\n",Heap_Minimum(array,size));
 	 	
 	printf("Before Heap_Decrease_Key:%n");
 	for(i = 0;i < size;i++)
 	{
	 	printf("%d ",array[i]);
	 }
	 
 	Heap_Decrease_Key(array,8,key);
 	
	printf("\nAfter Heap_Decrease_Key:%n");
 	for(i = 0;i < size;i++)
 	{
	 	printf("%d ",array[i]);
	 }
	printf("\n");
	
	key = 30;
	printf("\nThe extract minmum element is:%d\n",Heap_Extract_Min(array,size));
	Min_Heap_Insert(array,key,size-1);
	printf("\nAfter Min_Heap_Insert:%n");
 	for(i = 0;i < size;i++)
 	{
	 	printf("%d ",array[i]);
	 }
	printf("\n");
 	
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
void Build_Min_Heap(int *array,int size)
{
	int i;
	for(i = size/2 - 1;i >=0;i--)
	{
		Min_HeapIfy(array,size,i);
	}
}
int Heap_Minimum(int *array,int size)
{
	return array[0];
}
int Heap_Extract_Min(int *array,int size)
{
	int min;
	if(size < 1)
	{
		printf("heap underflow!\n");
	}
	min = array[0];
	array[0] = array[size - 1];
	size = size - 1;
	Min_HeapIfy(array,size,0);
	return min;
}
void Heap_Decrease_Key(int *array,int i,int key)
{
	int ParIndex = (i - 1)/2;
	int temp;
	if(key > array[i])
	{
		printf("new key is bigger than current key");
	}
	array[i] = key;
	while(i > 0 && array[ParIndex] > array[i])
	{
		temp = array[i];
		array[i] = array[ParIndex];
		array[ParIndex] = temp;
		i = ParIndex;
	}	
}
void Min_Heap_Insert(int *array,int key,int size)
{
	size = size + 1;
	array[size - 1] = INT_MAX;
	Heap_Decrease_Key(array,size - 1,key);
}