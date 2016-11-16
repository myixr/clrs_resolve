/*--------2016.11.16----------*
*-introduction to algorithms-*
*-----------8.3-1------------*
*---------RADIX SORT---------*/

#include <stdio.h>
#include <stdlib.h>


void Radix_sort(char **arrayA,int size,int d);

int main()
{
	char *A[16] = {"COW","DOG","SEA","RUG","ROW","MOB","BOX",
					"TAB","BAR","EAR","TAR","DIG","BIG","TEA","NOW","FOX"};
	int size  = 16;
	int d = 3;
	int i,j;
	Radix_sort(A,size,d);
	printf("After Radix sort:\n");
	for(i = 0;i < size;i++)
	{
		printf("%s\n",A[i]);
	}	
	return 0;
}

void Radix_sort(char **arrayA,int size,int d)
{
	int i,j,m,key;
	char *tempA = (char *)malloc(d * sizeof(char));
	for(i = d - 1;i >= 0;i--)
	{
		for(j = 1;j < size;j++)
		{
			key = arrayA[j][i];
			tempA = arrayA[j];
			m = j - 1;
			while(m >= 0 && arrayA[m][i] > key)
			{
				arrayA[m +1] = arrayA[m];
				m = m - 1;
			}
			arrayA[m + 1] = tempA;
		}	
	}

}