/*---2016.10.24---*
*-introduction to algorithms-*
*----4.1-2----*
*-Max sub array problem---recursive algorithm-*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 10
typedef struct{
	int LeftIndex;
	int RightIndex;
	int MaxSubSum;
}MaxSubInfo;

MaxSubInfo MaxCrossSub_Recursive(const int *array,int low,int mid,int high);
MaxSubInfo MaxSub_Recursive(const int *array,int low,int high);

int main()
{
	int array[N] = {-4,9,-12,19,6,-23,-5,30,15,-21};
	int i;
	MaxSubInfo Info;
	Info = MaxSub_Recursive(array,0,N-1);

	printf("Max sub array:\n");
	printf("Sum:%d\n",Info.MaxSubSum);
	printf("LeftIndex:%d\n",Info.LeftIndex);
	printf("RightIndex:%d\n",Info.RightIndex);
	
	return 0;
}
MaxSubInfo MaxCrossSub_Recursive(const int *array,int low,int mid,int high)
{
	MaxSubInfo MaxSumInfo;
	int LeftSum = INT_MIN,RightSum = INT_MIN;
	int tempSum = 0;
	int i,j;
	for(i = mid;i >= low;i--)
	{
		tempSum += array[i];
		if(tempSum > LeftSum)
		{
			LeftSum = tempSum;
			MaxSumInfo.LeftIndex = i;
		}	
	}
	tempSum = 0;
	for(j = mid+1;j <= high;j++)
	{
		tempSum += array[j];
		if(tempSum > RightSum)
		{
			RightSum = tempSum;
			MaxSumInfo.RightIndex = j;
		}
	}
	MaxSumInfo.MaxSubSum = LeftSum + RightSum;
	
	return MaxSumInfo;
}
MaxSubInfo MaxSub_Recursive(const int *array,int low,int high)
{
	MaxSubInfo Info,LeftInfo,RightInfo,CrossInfo;
	int mid;
	if(high == low)
	{
		Info.LeftIndex = low;
		Info.RightIndex = high;
		Info.MaxSubSum = array[low];
		return Info;
	}
	else 
	{
		mid = (low + high)/2;
		LeftInfo = MaxSub_Recursive(array,low,mid);
		RightInfo = MaxSub_Recursive(array,mid+1,high);
		CrossInfo = MaxCrossSub_Recursive(array,low,mid,high);
	}
	if((LeftInfo.MaxSubSum >= RightInfo.MaxSubSum)&&(LeftInfo.MaxSubSum >= CrossInfo.MaxSubSum))
		return LeftInfo;
	else if((RightInfo.MaxSubSum >= LeftInfo.MaxSubSum)&&(RightInfo.MaxSubSum >= CrossInfo.MaxSubSum))
		return RightInfo;
	else
		return CrossInfo;
	
}