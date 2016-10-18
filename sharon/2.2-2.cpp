/*---2016.10.17---*
*-introduction to algorithms-*
*----2.2-2----*
*-selection sort-*/

#include <stdio.h>

#define N 10

void Select_sort(int *array);

int main()
{
	int array[N] = {4,9,12,19,6,23,5,30,15,21};
	int i;
	Select_sort(array);

	printf("After selection sort:");
	for(i = 0;i < N;i++)
	{
		printf("\t%d",array[i]);
	}
	printf("\n");
	
	return 0;
}
void Select_sort(int *array)
{
	int i,j,temp,nIndex;
	for(i = 0;i < N-1;i++)
	{
		nIndex = i;
		for(j = i;j < N;j++)
		{
			if(array[nIndex] > array[j])
				nIndex = j;
		}
		if(nIndex != i)
		{
			temp = array[i];
			array[i] = array[nIndex];
			array[nIndex] = temp;			
		}
	}
}
