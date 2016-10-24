/*---2016.10.24---*
*-introduction to algorithms-*
*----4.1-2----*
*-Max sub array problem---Violent solution-*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 10
typedef struct{
	int LeftIndex;
	int RightIndex;
	int MaxSubSum;
}MaxSubInfo;
MaxSubInfo MaxSub_Violent(const int *array);

int main()
{
	int array[N] = {-4,9,-12,19,6,-23,-5,30,15,-21};
	int i;
	MaxSubInfo Info;
	Info = MaxSub_Violent(array);

	printf("Max sub array:\n");
	printf("Sum:%d\n",Info.MaxSubSum);
	printf("LeftIndex:%d\n",Info.LeftIndex);
	printf("RightIndex:%d\n",Info.RightIndex);
	
	return 0;
}
MaxSubInfo MaxSub_Violent(const int *array)
{
	MaxSubInfo Info;
	int i,j,k;
	Info.MaxSubSum = INT_MIN;
	for(i = 0;i < N;i++)
	{
		for(j = i;j < N;j++)
		{
			int temp = 0;
			for(k = i;k <= j;k++)
				temp += array[k];
			if(temp > Info.MaxSubSum)
				{
					Info.MaxSubSum = temp;
					Info.LeftIndex = i;
					Info.RightIndex = j;
				}
					
		}
			
	}
	
	return Info;
}

