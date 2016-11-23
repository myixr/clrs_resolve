/*--------2016.11.23----------*
*-introduction to algorithms-*
*-----------9.3-7------------*
*----CLOSEST MEDIAN NUMBER----*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Rand_Select(int *array,int p,int r,int i);
int Rand_Partition(int *array,int p,int r);
void Median_Closest(int *array,int size,int k);
int main()
{
	int array[] = {3,2,9,0,7,5,4,8,6,1};

	int size = 10;
	int k = 4;
		 	
	printf("%d closest median numbers:\n",k);
	Median_Closest(array,size,k);
	
	return 0;
}

int Rand_Partition(int *array,int p,int r)
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
int Rand_Select(int *array,int p,int r,int i)
{
	int q,k;
	if(p == r)
	{
		return array[p];
	}
	q = Rand_Partition(array,p,r);
	k = q - p + 1;
	if(i == k)
	{
		return array[q];
	}
	else if(i < k)
	{
		return Rand_Select(array,p,q - 1,i);
	}
	else
	{
		return Rand_Select(array,q + 1,r,i - k);
	}
}
void Median_Closest(int *array,int size,int k)
{
	int i = (int)((size + 1)/2);//median	
	int m = Rand_Select(array,0,size - 1,i);
	int j,t;
	int *tempA = (int *)malloc(size * sizeof(int));
	int *tempB = (int *)malloc(size * sizeof(int));
	for(j = 0;j < size;j++)
	{
		tempA[j] = abs(array[j] - m);
		tempB[j] = tempA[j];
	}
	t = Rand_Select(tempB,0,size - 1,k);

	for(j = 0;j < size;j++)
	{
		if(tempA[j] <= t && tempA[j] != 0)
		{
			printf("%d\t",array[j]);
		}
	}
	free(tempA);
	free(tempB);
}