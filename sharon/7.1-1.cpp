/*--------2016.11.9----------*
*-introduction to algorithms-*
*-----------7.1-1------------*
*---------QUICKSORT----------*/

#include <stdio.h>
#include <stdlib.h>

void Quick_Sort(int *array,int p,int r);
int Partition(int *array,int p,int r);

int main()
{
	int array[] = {13,19,9,5,12,8,7,4,21,2,6,11};

	int size = 12;
	int i;
		
	Quick_Sort(array, 0,size - 1);
		 	
 	printf("After Quick Sort:%n");
 	for(i = 0;i < size;i++)
 	{
	 	printf("%d ",array[i]);
	 }
 	printf("\n");
	return 0;
}
void Quick_Sort(int *array,int p,int r)
{
	int q;
	if(p < r)
	{
		q = Partition(array,p,r);
		Quick_Sort(array,p,q - 1);
		Quick_Sort(array,q + 1,r);	
	}
}

int Partition(int *array,int p,int r)
{
	int x = array[r];
	int i = p - 1;
	int j,temp;
	for(j = p;j < r;j++)
	{
		if(array[j] <= x)
		{
			i = i + 1;
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	temp = array[i+1];
	array[i+1] = array[r];
	array[r] = temp;
	return i+1;
}

