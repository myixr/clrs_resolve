#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>


/* 
 * @brief 矩阵数据定义
 * 
 * 矩阵数据可以有多个矩阵头共享。
 */
typedef struct MatrixData{
	float *elems;  /* 数据 */
	int ref_count; /* 引用计数 */
	int rows;      /* 行数 */
	int cols;      /* 列数 */
}matrix_data_t;

/*
 * @brief 矩阵头定义
 */
typedef struct MatrxHeader{
	matrix_data_t *data;
	int start_row; /* 开始行 */
	int start_col; /* 开始列 */
	int rows;      /* 矩阵的行数 */
	int cols;      /* 矩阵的列数 */
}matrix_header_t;

/* 打印矩阵内容 */
void matrix_print( const matrix_header_t *m );
/* 
 * @brief 矩阵赋值 
 * 将from指向的矩阵赋值给to指向的矩阵
 * 确保两个矩阵具有相同的大小且不能指向同一个数据实体
 */
void matrix_assign( matrix_header_t *to, const matrix_header_t *from );
/* 
 * @brief 创建新矩阵 
 * 创建一个新的矩阵，并保存在m中
 * 确保m已经被初始化并且为空矩阵
 */
int matrix_new( matrix_header_t *m, int rows, int cols );
/* 
 * @brief 释放矩阵
 * 释放矩阵，减少矩阵数据实体的引用计数，如果
 * 引用计数减少到0，则释放数据实体
 */
void matrix_free( matrix_header_t *m );
/* 
 * @brief 初始化矩阵头 
 * 初始化矩阵头，初始化后为空矩阵（不指向任何矩阵数据实体）
 */
void matrix_initHeader( matrix_header_t *m );

/*
 * @brief 用某个值填充矩阵
 * 调用后矩阵m中的所有元素的值都是value
 */
void matrix_fullValue( matrix_header_t *m, float value );

/*
 * @brief 用某个值填充矩阵
 * 调用后矩阵m中的所有元素的值都是value
 */
void matrix_fullRandomValue( matrix_header_t *m );

/*
 * @brief 创建子矩阵
 * 创建m矩阵的子矩阵,两个矩阵共享数据
 * 确保sub是空矩阵
 */
void matrix_subMatrix( matrix_header_t *sub, const matrix_header_t *m, int start_row, int start_col, int rows, int cols );

/*
 * @brief 矩阵相加
 * result = m1+m2
 *
 * 如果result矩阵为空，则为result创建新的矩阵
 */
void matrix_add( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 );

/*
 * @brief 矩阵相减
 * result = m1-m2
 *
 * 如果result矩阵为空，则为result创建新的矩阵
 */
void matrix_subtract( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 );

/*
 * @brief 矩阵相乘
 * 普通矩阵乘法，result = m1 * m2, 复杂度为n^3
 *
 * 如果result矩阵为空，则为result创建新的矩阵
 */
void matrix_multi( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 );

void matrix_strassen( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 );


static inline float matrix_getElem( const matrix_header_t *m, int row, int col ){
	assert( row < m->rows );
	assert( col < m->cols );
	int idx = (m->start_row+row)*m->data->cols + (m->start_col+col);
	return m->data->elems[idx];
}

static inline void matrix_setElem( matrix_header_t *m, int row, int col, float value ){
	assert( row < m->rows );
	assert( col < m->cols );
	int idx = (m->start_row+row)*m->data->cols + (m->start_col+col);
	m->data->elems[idx] = value;
}

void matrix_assign( matrix_header_t *to, const matrix_header_t *from ){
	assert( from->rows == to->rows );
	assert( from->cols == to->cols );
	assert( from->data != to->data );

	for( int r=0; r<from->rows; ++r ){
		for( int c=0; c<from->cols; ++c ){
			matrix_setElem( to, r, c,
					matrix_getElem( from, r, c ) );
		}
	}
}

void matrix_print( const matrix_header_t *m ){
	printf( "Matrix @%lx\n", (unsigned long)m->data );
	printf( "       rows=%d cols=%d\n", m->rows,m->cols );
	for( int r=0; r<m->rows; ++r ){
		printf( "  " );
		for( int c=0; c<m->cols; ++c ){
			printf( "%f ", matrix_getElem( m,r,c ) );
		}
		printf( "\n" );
	}
}

int matrix_new( matrix_header_t *m, int rows, int cols ){
	assert( m->data == NULL );
	m->data = (matrix_data_t*)calloc( sizeof(matrix_data_t),1 );
	m->data->elems = (float*)calloc( sizeof(float), rows*cols );
	m->data->rows = rows;
	m->data->cols = cols;
	m->data->ref_count = 1;

	m->start_row = 0;
	m->start_col = 0;
	m->rows = rows;
	m->cols = cols;

	return 0;
}

void matrix_free( matrix_header_t *m ){
	if( m->data == 0 ){
		return;
	}

	m->data->ref_count --;
	if( m->data->ref_count <= 0 ){
		free( m->data->elems );
		free( m->data );
	}

	matrix_initHeader( m );
}

void matrix_initHeader( matrix_header_t *m ){
	m->data = NULL;
	m->rows = 0;
	m->cols = 0;
	m->start_row = 0;
	m->start_col = 0;
}

void matrix_subMatrix( matrix_header_t *sub, const matrix_header_t *m, int start_row, int start_col, int rows, int cols ){
	assert( sub->data == NULL );
	assert( m->rows >= start_row+rows );
	assert( m->cols >= start_col+cols );

	sub->data = m->data;
	sub->data->ref_count ++;

	sub->start_row = m->start_row + start_row;
	sub->start_col = m->start_col + start_col;
	sub->rows = rows;
	sub->cols = cols;
}

void matrix_fullValue( matrix_header_t *m, float value ){
	assert( m->data != NULL );

	for( int r=0; r<m->rows; ++r ){
		for( int c=0; c<m->cols; ++c ){
			matrix_setElem( m, r,c, value );
		}
	}
}

void matrix_add( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 ){
	assert( m1->rows == m2->rows );
	assert( m1->cols == m2->cols );
	
	if( result->data == NULL ){
		matrix_new( result, m1->rows, m1->cols );
	}
	else{
		assert( result->rows == m1->rows );
		assert( result->cols == m1->cols );
	}

	for( int r=0; r<result->rows; ++r ){
		for( int c=0; c<result->cols; ++c ){
			matrix_setElem( result, r,c,
					matrix_getElem( m1, r,c ) +
					matrix_getElem( m2, r,c ) );
		}
	}
}

void matrix_subtract( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 ){
	assert( m1->rows == m2->rows );
	assert( m1->cols == m2->cols );
	
	if( result->data == NULL ){
		matrix_new( result, m1->rows, m1->cols );
	}
	else{
		assert( result->rows == m1->rows );
		assert( result->cols == m1->cols );
	}

	for( int r=0; r<result->rows; ++r ){
		for( int c=0; c<result->cols; ++c ){
			matrix_setElem( result, r,c,
					matrix_getElem( m1, r,c ) -
					matrix_getElem( m2, r,c ) );
		}
	}
}

void matrix_multi( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 ){
	assert( m1->cols == m2->rows );
	if( result->data == NULL ){
		matrix_new( result, m1->rows, m2->cols );
	}
	else{
		assert( result->rows == m1->rows );
		assert( result->cols == m2->cols );
	}


	for( int i=0; i<m1->rows; ++i ){
		for( int j=0; j<m2->cols; ++j ){
			float elem = 0;
			for( int k=0; k<m1->cols; ++k ){
				elem += matrix_getElem( m1, i,k ) *
					matrix_getElem( m2, k,j );
			}
			matrix_setElem( result, i,j, elem );
		}
	}
}

void matrix_fullRandomValue( matrix_header_t *m ){
	int r,c;
	for( r=0; r<m->rows; ++r ){
		float value = (rand()%10000-5000)/5000.0;
		for( c=0; c<m->cols; ++c ){
			matrix_setElem( m, r,c, value );
		}
	}
}

void matrix_strassen( matrix_header_t *result, const matrix_header_t *m1, const matrix_header_t *m2 ){
	assert( result->data == NULL );
	assert( m1->rows == m1->cols );
	assert( m2->rows == m2->cols );
	assert( m1->rows == m2->rows );

	if( result->data == NULL ){
		matrix_new( result, m1->rows, m1->cols );
	}

	/* 递归结束条件 */
	if( m1->rows == 1 ){
		matrix_setElem( result, 0,0, matrix_getElem(m1,0,0)*matrix_getElem(m2,0,0) );
		return;
	}

	matrix_header_t a11,a12,a21,a22;
	matrix_header_t b11,b12,b21,b22;
	matrix_header_t c11,c12,c21,c22;
	matrix_initHeader( &a11 );
	matrix_initHeader( &a12 );
	matrix_initHeader( &a21 );
	matrix_initHeader( &a22 );
	matrix_initHeader( &b11 );
	matrix_initHeader( &b12 );
	matrix_initHeader( &b21 );
	matrix_initHeader( &b22 );
	matrix_initHeader( &c11 );
	matrix_initHeader( &c12 );
	matrix_initHeader( &c21 );
	matrix_initHeader( &c22 );

	int n = m1->rows/2;
	matrix_subMatrix( &a11, m1, 0,0, n,n );
	matrix_subMatrix( &a12, m1, 0,n, n,n );
	matrix_subMatrix( &a21, m1, n,0, n,n );
	matrix_subMatrix( &a22, m1, n,n, n,n );

	matrix_subMatrix( &b11, m2, 0,0, n,n );
	matrix_subMatrix( &b12, m2, 0,n, n,n );
	matrix_subMatrix( &b21, m2, n,0, n,n );
	matrix_subMatrix( &b22, m2, n,n, n,n );

	matrix_subMatrix( &c11, result, 0,0, n,n );
	matrix_subMatrix( &c12, result, 0,n, n,n );
	matrix_subMatrix( &c21, result, n,0, n,n );
	matrix_subMatrix( &c22, result, n,n, n,n );

	matrix_header_t s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
	matrix_initHeader( &s1 );
	matrix_initHeader( &s2 );
	matrix_initHeader( &s3 );
	matrix_initHeader( &s4 );
	matrix_initHeader( &s5 );
	matrix_initHeader( &s6 );
	matrix_initHeader( &s7 );
	matrix_initHeader( &s8 );
	matrix_initHeader( &s9 );
	matrix_initHeader( &s10 );

	matrix_subtract( &s1, &b12, &b22 );
	matrix_add(      &s2, &a11, &a12 );
	matrix_add(      &s3, &a21, &a22 );
	matrix_subtract( &s4, &b21, &b11 );
	matrix_add(      &s5, &a11, &a22 );
	matrix_add(      &s6, &b11, &b22 );
	matrix_subtract( &s7, &a12, &a22 );
	matrix_add(      &s8, &b21, &b22 );
	matrix_subtract( &s9, &a11, &a21 );
	matrix_add(      &s10,&b11, &b12 );

	matrix_header_t p1,p2,p3,p4,p5,p6,p7;
	matrix_initHeader( &p1 );
	matrix_initHeader( &p2 );
	matrix_initHeader( &p3 );
	matrix_initHeader( &p4 );
	matrix_initHeader( &p5 );
	matrix_initHeader( &p6 );
	matrix_initHeader( &p7 );

	matrix_strassen( &p1, &a11, &s1 );
	matrix_strassen( &p2, &s2, &b22 );
	matrix_strassen( &p3, &s3, &b11 );
	matrix_strassen( &p4, &a22, &s4 );
	matrix_strassen( &p5, &s5, &s6 );
	matrix_strassen( &p6, &s7, &s8 );
	matrix_strassen( &p7, &s9, &s10 );

	/* c11 = p5 + p4 - p2 + p6 */
	matrix_add( &c11, &p5, &p4 );
	matrix_subtract( &c11, &c11, &p2 );
	matrix_add( &c11, &c11, &p6 );

	/* c12 = p1 + p2 */
	matrix_add( &c12, &p1, &p2 );

	/* c21 = p3 + p4 */
	matrix_add( &c21, &p3, &p4 );

	/* c22 = p5 + p1 -p3 -p7 */
	matrix_add( &c22, &p5, &p1 );
	matrix_subtract( &c22, &c22, &p3 );
	matrix_subtract( &c22, &c22, &p7 );

	matrix_free( &a11 );
	matrix_free( &a12 );
	matrix_free( &a21 );
	matrix_free( &a22 );
	matrix_free( &b11 );
	matrix_free( &b12 );
	matrix_free( &b21 );
	matrix_free( &b22 );
	matrix_free( &c11 );
	matrix_free( &c12 );
	matrix_free( &c21 );
	matrix_free( &c22 );
	matrix_free( &s1 );
	matrix_free( &s2 );
	matrix_free( &s3 );
	matrix_free( &s4 );
	matrix_free( &s5 );
	matrix_free( &s6 );
	matrix_free( &s7 );
	matrix_free( &s8 );
	matrix_free( &s9 );
	matrix_free( &s10 );
	matrix_free( &p1 );
	matrix_free( &p2 );
	matrix_free( &p3 );
	matrix_free( &p4 );
	matrix_free( &p5 );
	matrix_free( &p6 );
	matrix_free( &p7 );
}

#define N 128

int main( void ){
	matrix_header_t m1;
	matrix_header_t m2;
	matrix_initHeader( &m1 );
	matrix_initHeader( &m2 );

	matrix_new( &m1, N, N );
	matrix_new( &m2, N, N );

	matrix_fullRandomValue( &m1 );
	matrix_fullRandomValue( &m2 );

	//matrix_print( &m1 );
	//matrix_print( &m2 );

	matrix_header_t m3;
	matrix_initHeader( &m3 );
	clock_t c1 = clock();
	matrix_strassen( &m3, &m1, &m2 );
	clock_t c2 = clock();

	matrix_header_t m4;
	matrix_initHeader( &m4 );
	clock_t c3 = clock();
	matrix_multi( &m4, &m1, &m2 );
	clock_t c4 = clock();

	//matrix_print( &m3 );
	//matrix_print( &m4 );

	matrix_free( &m1 );
	matrix_free( &m2 );
	matrix_free( &m3 );
	matrix_free( &m4 );

	printf( "-------------------------\n" );
	printf( "Matrix size : %d\n", N );
	printf( " matrix multiply time: %f\n", (double)(c2-c1)/CLOCKS_PER_SEC );
	printf( " strassen method time: %f\n", (double)(c4-c3)/CLOCKS_PER_SEC );
}

