/*---2016.10.17---*
*-introduction to algorithms-*
*----2.1-4----*
*-Binary integer addition-*/

#include <stdio.h>
#include <math.h>
#define N 10

void Binary_add(char *arrayA,char *arrayB,char *arrayC);

int main()
{
	char arrayA[N] = {0,1,1,1,0,0,0,1,1,1};
	char arrayB[N] = {1,1,1,0,1,0,1,1,0,1};
	char arrayC[N+1] = {0};
	int i;
	Binary_add(arrayA,arrayB,arrayC);

	printf("After Binary integer addition:");
	for(i = N;i >= 0;i--)
	{
		printf("%d",arrayC[i]);
	}
	printf("\n");
	
	return 0;
}
void Binary_add(char *arrayA,char *arrayB,char *arrayC)
{
	char temp = 0;
	int i,j;
	j = 0;
	for(i = N-1;i >=0;i--)
	{
		printf("%d\t",arrayA[i]);
		printf("%d\t",arrayB[i]);
		printf("%d\t",temp);
		arrayC[j] = (!temp&(arrayA[i]^arrayB[i]))|(temp&(!(arrayA[i]^arrayB[i])));
		printf("%d\n",arrayC[j]);
		temp = (arrayA[i]&arrayB[i])|(temp&arrayA[i])|(temp&arrayB[i]);
		j++;
	}
	arrayC[j] = temp;	
}
