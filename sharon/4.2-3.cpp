/*---2016.10.26---*
*-introduction to algorithms-*
*----4.2-3----*
*-Strassen algorithm for matrix multiplication-*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int cols;
	int rows;
	int *data;
}matrix;
matrix *matrix_copy(const matrix *A);
matrix *matrix_add(matrix *A,matrix *B);
matrix *matrix_sub(matrix *A,matrix *B);
matrix **matrix_split_re0(const matrix *A);
matrix **matrix_get_sub(const matrix *A);
matrix *matrix_merge(matrix *A,matrix *B,matrix *C,matrix *D);
matrix *matrix_multi_recursion(matrix *A,matrix *B);

int main()
{
	matrix *A = (matrix *)malloc(sizeof(matrix));
	matrix *B = (matrix *)malloc(sizeof(matrix));
	matrix *C = (matrix *)malloc(sizeof(matrix));
	int i,j;
	
	A->cols = 3;
	A->rows = 2;
	B->cols = 2;
	B->rows = 3;
	A->data = (int *)malloc(6*sizeof(int));
	B->data = (int *)malloc(6*sizeof(int));
	int X[6] = {1,0,1,2,1,0};
	int Y[6] = {1,3,0,1,2,2};
	for(i = 0;i < 6;i++)
	{
		A->data[i] = X[i];
		B->data[i] = Y[i];
	}
	C = matrix_multi_recursion(A,B);

	printf("A * B :\n");

	for(i = 0;i < C->rows;i++)
	{
		for(j = 0;j < C->cols;j++)
		{
			printf("%d\t",C->data[i*C->cols + j]);
			if(j == C->cols -1)
			{
				printf("\n");
			}
		}
	}
	free(A->data);
	free(B->data);
	free(A);
	free(B);
	free(C);
	return 0;
}
matrix *matrix_copy(const matrix *A)
{
	int i;
	matrix *B = (matrix *)malloc(sizeof(matrix));
	B->cols = A->cols;
	B->rows = A->rows;
	B->data = (int *)malloc(B->cols*B->rows*sizeof(int));
	for(i = 0;i < B->cols*B->rows;i++)
	{
		B->data[i] = A->data[i];
	}
	
	return B;
}
matrix *matrix_add(matrix *A,matrix *B)
{
	matrix *C = (matrix *)malloc(sizeof(matrix));

	int i;
	if(A == NULL && B != NULL)
	{
		return matrix_copy(B);
	}
	else if(B== NULL && A != NULL)
	{
		return matrix_copy(A);
	}
	else if(A == NULL && B == NULL)
	{
		return NULL;
	}
	else
	{	
		C->cols = A->cols;
		C->rows = A->rows;
		C->data = (int *)malloc(A->cols*A->rows*sizeof(int));
		for(i = 0;i < A->rows * A->cols;i++)
		{
			C->data[i] = A->data[i] + B->data[i];	
		}
	
	}
	return C;
}
matrix *matrix_sub(matrix *A,matrix *B)
{
	matrix *C = (matrix *)malloc(sizeof(matrix));

	int i;
	if(A == NULL && B != NULL)
	{
		C->data = (int *)malloc(B->cols*B->rows*sizeof(int));
		for(i = 0;i < B ->rows * B ->cols;i++)
		{
			C->data[i] = 0 - B->data[i];	
		}
		C->cols = B->cols;
		C->rows = B->rows;
		
		return C;
	}
	else if(B== NULL && A != NULL)
	{
		return matrix_copy(A);
	}
	else if(A == NULL && B == NULL)
	{
		return NULL;
	}
	else
	{
		C->data = (int *)malloc(A->cols*A->rows*sizeof(int));
		for(i = 0;i < A ->rows * A ->cols;i++)
		{
			C->data[i] = A->data[i] - B->data[i];	
		}
		C->cols = A->cols;
		C->rows = A->rows;	
	}

	return C;
}
matrix **matrix_split_re0(const matrix *A)
{
	int i,j;
	matrix **S = (matrix **)malloc(4 * sizeof(matrix *));
	int r = A->rows%2 == 0?A->rows/2:(A->rows+1)/2;
	int c = A->cols%2 == 0?A->cols/2:(A->cols+1)/2;
	
	S[0] = (matrix *)malloc(sizeof(matrix));
	S[1] = (matrix *)malloc(sizeof(matrix));
	S[2] = (matrix *)malloc(sizeof(matrix));
	S[3] = (matrix *)malloc(sizeof(matrix));
	S[0]->cols = c;S[0]->rows = r;
	S[1]->cols = A->cols - c;S[1]->rows = r;
	S[2]->cols = c;S[2]->rows = A->rows - r;
	S[3]->cols = A->cols - c;S[3]->rows = A->rows - r;
	S[0]->data = (int *)malloc(r * c * sizeof(int));
	S[1]->data = (int *)malloc(r * (A->cols - c )* sizeof(int));
	S[2]->data = (int *)malloc((A->rows - r) * c * sizeof(int));
	S[3]->data = (int *)malloc((A->rows - r) * (A->cols - c ) * sizeof(int));
	for(i = 0;i < r;i++)
	{
		for(j = 0;j < c;j++)
		{
			S[0]->data[i*c + j] = A->data[i*A->cols + j];
		}
	}
	for(i = 0;i < r;i++)
	{
		for(j = 0;j < A->cols - c;j++)
		{
			S[1]->data[i*S[1]->cols + j] = A->data[i*A->cols + j + c];
		}
	}
	for(i = 0;i < A->rows - r;i++)
	{
		for(j = 0;j <  c;j++)
		{
			S[2]->data[i*c + j] = A->data[(i+r)*A->cols + j];
		}
	}
	for(i = 0;i < A->rows - r;i++)
	{
		for(j = 0;j < A->cols - c;j++)
		{
			S[3]->data[i*S[3]->cols + j] = A->data[(i+r)*A->cols + j + c];
		}
	}
	
	return S;	
}
matrix **matrix_get_sub(const matrix *A)
{
	int i,j;
	matrix **S = (matrix **)malloc(4 * sizeof(matrix *));
	int n = A->rows > A->cols ? A->cols:A->rows;
	if(n%2 != 0)
	{
		n = n-1;
	}
	S[0] = (matrix *)malloc(sizeof(matrix));
	S[1] = (matrix *)malloc(sizeof(matrix));
	S[2] = (matrix *)malloc(sizeof(matrix));
	S[3] = (matrix *)malloc(sizeof(matrix));
	S[0]->cols = n;S[0]->rows = n;
	S[1]->cols = A->cols - n;S[1]->rows = n;
	S[2]->cols = n;S[2]->rows = A->rows - n;
	S[3]->cols = A->cols - n;S[3]->rows = A->rows - n;
	S[0]->data = (int *)malloc(n * n * sizeof(int));
	S[1]->data = (int *)malloc(n * (A->cols - n )* sizeof(int));
	S[2]->data = (int *)malloc((A->rows - n) * n * sizeof(int));
	S[3]->data = (int *)malloc((A->rows - n) * (A->cols - n ) * sizeof(int));
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			S[0]->data[i*n + j] = A->data[i*A->cols + j];
		}
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < A->cols - n;j++)
		{
			S[1]->data[i*S[1]->cols + j] = A->data[i*A->cols + j + n];
		}
	}
	for(i = 0;i < A->rows - n;i++)
	{
		for(j = 0;j <  n;j++)
		{
			S[2]->data[i*n + j] = A->data[(i+n)*A->cols + j];
		}
	}
	for(i = 0;i < A->rows - n;i++)
	{
		for(j = 0;j < A->cols - n;j++)
		{
			S[3]->data[i*S[3]->cols + j] = A->data[(i+n)*A->cols + j + n];
		}
	}
	
	return S;
}
matrix *matrix_merge(matrix *A,matrix *B,matrix *C,matrix *D)
{
		int i,j;
		matrix *SC = (matrix *)malloc(sizeof(matrix));
		A->cols = A != NULL ? A->cols:0;
		A->rows = A != NULL ? A->rows:0;
		B->cols = B != NULL ? B->cols:0;
		C->rows = C != NULL ? C->rows:0;

		SC->cols = A->cols + B->cols;
		SC->rows = A->rows + C->rows;
		SC->data = (int *)malloc(SC->cols * SC->rows *sizeof(int));
		if(A != NULL)
		{
			for(i = 0;i < A->rows;i++)
			{
				for(j = 0;j < A->cols;j++)
				{
					SC->data[i*SC->cols + j] = A->data[i*A->cols + j];
				}
			}	
		}
		if(B != NULL)
		{
			for(i = 0;i < B->rows;i++)
			{
				for(j = 0;j < B->cols;j++)
				{
					SC->data[i*SC->cols + j + A->cols] = B->data[i*B->cols + j];
				}
			}	
		}
		if(C != NULL)
		{
			for(i = 0;i < C->rows;i++)
			{
				for(j = 0;j < C->cols;j++)
				{
					SC->data[(i+ A->rows)*SC->cols + j ] = C->data[i*C->cols + j];
				}
			}
		}
		if(D != NULL)
		{
			for(i = 0;i < D->rows;i++)
			{
				for(j = 0;j < D->cols;j++)
				{
					SC->data[(i+ A->rows)*SC->cols + j + A->cols] = D->data[i*D->cols + j];
				}
			}
		}

		return SC;
}
matrix *matrix_multi_recursion(matrix *A,matrix *B)
{
	matrix *C = (matrix *)malloc(sizeof(matrix));
	int i,j,k;
	if(A == NULL || B == NULL)
	{
		return NULL;
	}
	if(A->cols < 2 || A->rows < 2 || B->cols < 2 || B->rows < 2)
	{
		C->cols = B->cols;
		C->rows = A->rows;
		C->data = (int *)malloc(A->rows * B->cols *sizeof(int));
		for(i = 0;i < A->rows;i++)
		{
			for(j = 0;j < B->cols;j++)
			{
				C->data[i* A->rows + j] = 0;
				for(k = 0;k < A->cols;k++)
				{
					C->data[i* A->cols + j] += A->data[i* A->cols + k] * B->data[j + k * B->cols];
				}
			}
		}
	return C;
	}
	else if(A->cols%2 != 0 || A->rows%2 != 0 || B->cols%2 != 0 || B->rows%2 != 0)
	{
		matrix **SA = matrix_get_sub(A);
		matrix **SB = matrix_get_sub(B); 
		matrix *a11 = SA[0],*a12 = SA[1],*a21 = SA[2],*a22 = SA[3];
		matrix *b11 = SB[0],*b12 = SB[1],*b21 = SB[2],*b22 = SB[3];

		matrix *C0 = matrix_add(matrix_multi_recursion(a11,b11),matrix_multi_recursion(a12,b21));
		matrix *C1 = matrix_add(matrix_multi_recursion(a11,b12),matrix_multi_recursion(a12,b22));
		matrix *C2 = matrix_add(matrix_multi_recursion(a21,a11),matrix_multi_recursion(a22,b21));
		matrix *C3 = matrix_add(matrix_multi_recursion(a21,b12),matrix_multi_recursion(a22,b22));

		C = matrix_merge(C0,C1,C2,C3);
		free(C0);
		free(C1);
		free(C2);
		free(C3);
		free(a11);
		free(a12);
		free(a21);
		free(a22);
		free(b11);
		free(b12);
		free(b21);
		free(b22);
		
		return C;
	}
	matrix **SA = matrix_split_re0(A);
	matrix **SB = matrix_split_re0(B);
	matrix *a11 = SA[0],*a12 = SA[1],*a21 = SA[2],*a22 = SA[3];
	matrix *b11 = SB[0],*b12 = SB[1],*b21 = SB[2],*b22 = SB[3];
	matrix *S1 = matrix_sub(b12,b22),*S2 = matrix_add(a11,a12),
	       *S3 = matrix_add(a21,a22),*S4 = matrix_sub(b21,b11),
		   *S5 = matrix_add(a11,a22),*S6 = matrix_add(b11,b22),
		   *S7 = matrix_sub(a12,a22),*S8 = matrix_add(b21,b22),
		   *S9 = matrix_sub(a11,a21),*S10 = matrix_add(b11,b12);
 	matrix *p1 = matrix_multi_recursion(a11,S1),
		   *p2 = matrix_multi_recursion(S2,b22),
	       *p3 = matrix_multi_recursion(S3,b11),
		   *p4 = matrix_multi_recursion(a22,S4),
		   *p5 = matrix_multi_recursion(S5,S6),
		   *p6 = matrix_multi_recursion(S7,S8),
		   *p7 = matrix_multi_recursion(S9,S10);
	matrix *C0 = matrix_add(matrix_sub(matrix_add(p5,p4),p2),p6);
	matrix *C1 = matrix_add(p1,p2);
	matrix *C2 = matrix_add(p3,p4);
	matrix *C3 = matrix_sub(matrix_sub(matrix_add(p5,p1),p3),p7);
	C = matrix_merge(C0,C1,C2,C3);
	free(a11);
	free(a12);
	free(a21);
	free(a22);
	free(b11);
	free(b12);
	free(b21);
	free(b22);
	free(S1);
	free(S2);
	free(S3);
	free(S4);
	free(S5);
	free(S6);
	free(S7);
	free(S8);
	free(S9);
	free(S10);
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);
	free(C0);
	free(C1);
	free(C2);
	free(C3);
	
	
	return C;
}