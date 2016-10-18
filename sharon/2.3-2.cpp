/*---2016.10.17---*
*-introduction to algorithms-*
*----2.3-2----*
*-Merging sort-*/

#include <stdio.h>
#include <stdlib.h>
#define N 10
void Merging(int *array,int p,int q,int r);
void Merge_sort(int *array,int p,int r);

int main()
{
	int array[N] = {4,9,12,19,6,23,5,30,15,21};
	int i;
	Merge_sort(array,0,N-1);

	printf("After Merging sort:");
	for(i = 0;i < N;i++)
	{
		printf("\t%d",array[i]);
	}
	printf("\n");
	
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
