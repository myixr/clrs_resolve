/*---2016.10.18---*
*-introduction to algorithms-*
*----2.3-5----*
*-Binary Search Algorithm-*/

#include <stdio.h>
#include <stdlib.h>
#define N 10

int Binary_Search(int *array,int v,int min,int max);
void Merging(int *array,int p,int q,int r);
void Merge_sort(int *array,int p,int r);

int main()
{
	int array[N] = {6,1,9,13,26,5,20,3,22,9};
	int i,v,index;
	Merge_sort(array,0,N-1);
	printf("After sort:\n");
	for(i = 0;i < N;i++)
		printf("\t%d",array[i]);
	
	printf("Enter a number:");
	scanf("%d",&v);
	index = Binary_Search(array,v,0,N-1);
	printf("After Binary Search Algorithm:");
	if(index != -1)
		printf("The index of %d is:%d",v,index);
	else 
		printf("There is no v in array");
	
	return 0;
}
void Merging(int *array,int p,int q,int r)
{
	int n1 = q - p;
	int n2 = r - q;

	int *L = (int *)malloc(sizeof(int)*n1);
	int *R = (int *)malloc(sizeof(int)*n2);
	int i,j,k;
	for(i = 0;i < n1;i++)
		L[i] = array[p + i];

	for(j = 0;j < n2;j++)
		R[j] = array[q + j];

	i = j = 0;
	k = p;
	while(i < n1 && j < n2)
	{
		if(L[i] <= R[j])
		{
			array[k++] = L[i];
			i++;
		}
		else
		{
			array[k++] = R[j];
			j++;
		}
	}
	if(i == n1)
		while(j < n2)
			array[k++] = R[j++];
	else
		while(i < n1)
			array[k++] = L[i++];
	
	free(L);
	free(R);
		
}
void Merge_sort(int *array,int p,int r)
{	
	int middle;
	if(p < r)
	{
		middle = (p + r)/2;
		Merge_sort(array,p,middle);
		Merge_sort(array,middle+1,r);
		Merging(array,p,middle+1,r+1);
	}
}

int Binary_Search(int *array,int v,int min,int max)
{
	int middle = (max + min)/2;
	if (min > max)
		return -1;
	else
	{
		if(array[middle] == v)
			return middle;
		else if(array[middle] < v)
			return Binary_Search(array,v,middle + 1,max);
		else
			return Binary_Search(array,v,min,middle - 1);	
	}
				
}

