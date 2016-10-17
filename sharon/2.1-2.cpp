/*---2016.10.17---*
*-introduction to algorithms-*
*----2.1-2----*
*-INSERTION-SORT  not ascending order-*/

#include <stdio.h>
#define N 10

void INSERTION_SORT(int *array,int length);

int main()
{
	int array[N] = {4,8,10,23,8,17,2,7,11,15};
	int length = N;
	int i;
	INSERTION_SORT(array,length);
	printf("After INSERTION SORT:");
	for(i = 0;i < length;i++)
		printf("\t%d",array[i]);
	printf("\n");
	return 0;
}
void INSERTION_SORT(int *array,int length)
{
	int i,j,key;
	for(j = 1;j < length;j++)
	{
		key = array[j];
		i = j - 1;
		while(i >= 0&&array[i] < key)
		{
			array[i+1] = array[i];
			i = i - 1;
		}
		array[i + 1] = key;
	}	
}