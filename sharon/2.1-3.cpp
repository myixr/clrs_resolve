/*---2016.10.17---*
*-introduction to algorithms-*
*----2.1-3----*
*-Linear search-*/

#include <stdio.h>
#define N 10

int Linear_search(int *array,int v);

int main()
{
	int array[N] = {4,8,10,23,8,17,2,7,11,15};
	int i,v;
	printf("please input the search value:");
	scanf("%d",&v);
	i = Linear_search(array,v);
	if(i < N )
		printf("The index of v in array is:%d\n",i);
	else
		printf("There is no v in array\n");
	return 0;
}
int Linear_search(int *array,int v)
{
	int i;
	for(i = 0;i < N;i++)
	{
		if(v == array[i])
	 		return i;
	}
	return i;	
}