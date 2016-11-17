#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 单向链表实现
 */

#define offsetof( type, member ) ((size_t) &((type *)0)->member )  
#define ELEM_OF_NODE(type,member,ptr) ((type*)( (char*)ptr-offsetof(type,member) ))

typedef struct ListNode{
    struct ListNode *next;
} list_node_t;
typedef struct ListNode *list_head_t;

void list_init( list_head_t *list );
void list_append( list_head_t list, list_node_t *node );
void list_destroy( list_head_t *list );
void list_foreach( list_head_t list, void(fun)(list_node_t*) );
void list_sort( list_head_t list, int (cmp)(list_node_t *,list_node_t*) );
list_node_t *list_next( list_node_t *node );

void list_init( list_head_t *list ){
	(*list) = (list_head_t)malloc( sizeof(list_node_t) );
	(*list)->next = NULL;
}

void list_append( list_head_t list, list_node_t *node ){
	if( list==NULL || node==NULL ){ return; }

	list_node_t *p = list;
	while( p && p->next!=NULL ){
		p = p->next;
	}

	p->next = node;
	node->next = NULL;
}

void list_destroy( list_head_t *list ){
	if( list==NULL || *list==NULL ){ return; }

	list_node_t *p = *list;
	list_node_t *p_next = NULL;
	*list = NULL;

	while( p ){
		p_next = p->next;
		free( p );
		p = p_next;
	}
}

void list_foreach( list_head_t list, void(fun)(list_node_t*) ){
	if( list==NULL || fun==NULL ){ return; 
	}
	list_node_t *p = list->next;
	while( p ){
		fun( p );
		p = p->next;
	}
}

void list_sort( list_head_t list, int (cmp)(list_node_t *,list_node_t*) ){
	/* 插入排序 */
	list_node_t *p = NULL;
	list_node_t *q = NULL;
	list_node_t *pre = list->next;
	
	while( pre ){
		p = pre->next;
		if( p == NULL ){ break; }

		/* 将p有序插入到链表中 */
		q = list;
		while( q != p ){
			if( cmp(p,q->next) ){
				pre->next = p->next;
				p->next = q->next;
				q->next = p;
				break;
			}
			q = q->next;
		}
		pre = pre->next;
	}
}

list_node_t *list_next( list_node_t *node ){
	return node->next;
}

/*
 * 桶排序实现
 */
struct BucketElem{
	list_node_t list_node;
	float value;
};

void printBucketElem( list_node_t *list_node ){
	struct BucketElem *elem = ELEM_OF_NODE( struct BucketElem, list_node, list_node );
	printf( "@%lxH: %f\n", (unsigned long)elem,  elem->value );
}

int cmpBucketElem( list_node_t *n1, list_node_t *n2 ){
	struct BucketElem *elem1 = ELEM_OF_NODE( struct BucketElem, list_node, n1 );
	struct BucketElem *elem2 = ELEM_OF_NODE( struct BucketElem, list_node, n2 );

	return (elem1->value<elem2->value);
}

void bucketSort( float values[], int len ){
	int n = len;
	int i = 0;
	int idx = 0;
	list_head_t *lists = (list_head_t*)malloc( sizeof(list_head_t)*n );

	for( i=0; i<n; ++i ){
		list_init( lists+i );
	}

	for( i=0; i<n; ++i ){
		struct BucketElem *elem = (struct BucketElem*)malloc( sizeof(struct BucketElem) );
		elem->value = values[i];
		list_append( lists[(int)floor(n*values[i])], &elem->list_node );
	}

	/* 输出链表中的内容 */
	/*
	for( i=0; i<n; ++i ){
		printf( "-- list %d --\n", i );
		list_foreach( lists[i], printBucketElem );
	}
	printf( "\n" );
	fflush( stdout );
	*/

	/* 排序各链表 */
	for( i=0; i<n; ++i ){
		fflush( stdout );	
		list_sort( lists[i], cmpBucketElem );
	}

	/* 输出链表中的内容 */
	/*
	for( i=0; i<n; ++i ){
		printf( "-- list %d --\n", i );
		list_foreach( lists[i], printBucketElem );
	}
	printf( "\n" );
	fflush( stdout );
	*/

	/* 将链表中的元素填到原数组中 */
	idx = 0;
	for( i=0; i<n; i++ ){
		list_node_t *node = lists[i];
		while( (node=list_next(node)) ){
			values[idx] = ELEM_OF_NODE( struct BucketElem, list_node, node )->value;
			idx ++;
		}

	}

	/* 销毁链表 */
	for( i=0; i<n; ++i ){
		list_destroy( lists+i );
	}
	free( lists );
}

/*
 * main
 */

int main( void ){
	int idx;
	float values[] = { 0.79,0.13,0.16,0.64,0.39,0.20,0.89,0.53,0.71,0.42,0.72,0.77,0.73,0.78 };
	
	printf( "-- Input --\n" );
	for( idx=0; idx<sizeof(values)/sizeof(float); ++idx ){
		printf( "%f ", values[idx] );
	}
	printf( "\n" );

	bucketSort( values, sizeof(values)/sizeof(float) );

	printf( "-- Output --\n" );
	for( idx=0; idx<sizeof(values)/sizeof(float); ++idx ){
		printf( "%f ", values[idx] );
	}
	printf( "\n" );
}