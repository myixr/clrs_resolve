/*--------2016.11.22----------*
*-introduction to algorithms-*
*-----------9.2-4------------*
*-----RANDOMIZED-SELECT------*/

#include <stdio.h>
#include <stdlib.h>

int Rand_Select(int *array,int p,int r,int i);
int Rand_Partition(int *array,int p,int r);

int main()
{
	int array[] = {3,2,9,0,7,5,4,8,6,1};

	int size = 10;
	int i = 1;
	
	int min = Rand_Select(array,0,size - 1,i);
		 	
	printf("The minmum number is:%d \n",min);

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
