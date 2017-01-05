/*--------2017.1.4----------*
*-introduction to algorithms-*
*-----------13------------*
*-----RED-BLACK BINARY SORT TREE------*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int key;
	int color; //1:red;0:black
	Node *p;
	Node *left;
	Node *right;
}Node;
typedef struct{
	Node *root;
	Node *nil;
}RB_Tree;


void Create_RB(RB_Tree *T,int *data,int len);

void LeftRotate_RB(RB_Tree *T,Node *x);
void RightRotate_RB(RB_Tree *T,Node *y);

Node *Search_RB(RB_Tree *T,Node *x,int k);
Node *Minimun_RB(RB_Tree *T,Node *x);
Node *Maximun_RB(RB_Tree *T,Node *x);
Node *Successor_RB(RB_Tree *T,Node *x);
void Inorder_RB(RB_Tree *T,Node *x);
void Insert_RB(RB_Tree *T,Node *z);
void InsertFixUp_RB(RB_Tree *T,Node *z);
void Transpant_RB(RB_Tree *T,Node *u,Node *v);
void Delete_RB(RB_Tree *T,Node *z);
void DeleteFixUp_RB(RB_Tree *T,Node *z);

int main()
{
	int data[] = {6,2,5,7,5,8};
	int len = sizeof(data)/sizeof(data[0]);
	int i;
	RB_Tree *T = (RB_Tree *)malloc(sizeof(RB_Tree));
	T->root = (Node *)malloc(sizeof(Node));
	T->root->color = 0;
	T->root->p = T->nil;
	
	T->nil = (Node *)malloc(sizeof(Node));
	T->nil->color = 0;
	T->nil->left = T->nil->right = NULL;
	T->nil->p = NULL;
	
	Create_RB(T,data,len);
	printf("Binary Sort Tree Elements:\n");
	Inorder_RB(T,T->root);
	printf("\n");
	
	int k = 5;
	Node *result = (Node *)malloc(sizeof(Node));
	printf("------Testing Search_BST.search elements k = %d-----\n",k);
	result = Search_RB(T,T->root,k);
	printf("The result of search elements %d:\n",result->key);
	
	result = Minimun_RB(T,T->root);
	printf("Minimum elements:%d\n",result->key);
	
	result = Maximun_RB(T,T->root);
	printf("Maximum elements:%d\n",result->key);
	
	result = Successor_RB(T,T->root);
	printf("Successor elements:%d\n",result->key);
	 
 	printf("------Testing Delete_BST------\n");
 	printf("Delete tree root:\n");
 	Delete_RB(T,T->root->left);
	printf("Binary Sort Tree Elements:\n");
	Inorder_RB(T,T->root);
	printf("\n");
	
	free(result);
	free(T->root);
	free(T->nil);
	free(T);
	return 0;
}
void Create_RB(RB_Tree *T,int *data,int len)
{
	int i;
	for(i = 0;i < len;i++)
	{
		Node *z = (Node *)malloc(sizeof(Node));
		if(z == NULL)
		{
			printf("In Create_BST,malloc failed!\n");
			return;
		}
		else
		{
			z->key = data[i];
			z->p = T->nil;
			z->left = T->nil;
			z->right = T->nil;
			z->color = 0;
			if(i ==0)
			{
				T->root = z;
			}
			else
			{
				Insert_RB(T,z);	
			}
			
		}
		
	}
	return;
}
//左旋操作使 
void LeftRotate_RB(RB_Tree *T,Node *x)
{
	Node *y = x->right; 
	x->right = y->left;
	if(y->left != T->nil)
		y->left->p = x;		//y 的左孩子变为x的右孩子
	y->p = x->p;			//y 指向x的父节点
	if(x->p == T->nil)
		T->root = y;		//如果x是根结点，则y变为根结点
	else if(x == x->p->left)
		x->p->left = y;		//如果x是其父节点的左孩子，则y替换为该节点的左孩子
	else 
		x->p->right = y;	//否则y替换为该节点的右孩子
	y->left = x;
	x->p= y; 
}
void RightRotate_RB(RB_Tree *T,Node *y)
{
	Node *x = y->left; 
	y->left = x->right;
	if(x->right != T->nil)
		x->right->p = y;	//x的右孩子变为y的左孩子
	x->p = y->p;			//x指向y的父节点
	if(y->p == T->nil)
		T->root = x;		//如果y是根结点，则x变为根结点
	else if(y == y->p->left)
		y->p->left = x;		//如果y是其父节点的左孩子，则x替换为该节点的左孩子
	else 
		y->p->right = x;	//否则x替换为该节点的右孩子
	x->right = y;
	y->p= x; 
}

void Insert_RB(RB_Tree *T,Node *z)
{
	Node *y = NULL;
	Node *x = T->root;
	while(x != T->nil)
	{
		y = x;
		if(z->key < x->key)
		{
			x = x->left;
		}else
		{
			x = x->right;
		}
	}
	z->p = y;
	if(y == T->nil)
	{
		T->root = z;
	}
	else if(z->key < y->key)
	{
		y->left = z;	
	}
	else
	{
		y->right = z;
	}
	z->left = T->nil;
	z->right = T->nil;
	z->color = 1;
	InsertFixUp_RB(T,z);
}
void InsertFixUp_RB(RB_Tree *T,Node *z)
{
	Node *y = NULL;
	while(z->p->color == 1)
	{
		if(z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if(y->color == 1)
			{
				z->p->color = 0;
				y->color = 0;
				z->p->p->color = 1;
				z = z->p->p;
			}
			else if(z == z->p->right)
			{
				z = z->p;
				LeftRotate_RB(T,z);
				z->p->color = 0;
				z->p->p->color = 1;
				RightRotate_RB(T,z->p->p);
			}
		}
		else
		{
			y = z->p->p->left;
			if(y->color == 1)
			{
				z->p->color = 0;
				y->color = 0;
				z->p->p->color = 1;
				z = z->p->p;
			}
			else if(z == z->p->left)
			{
				z = z->p;
				RightRotate_RB(T,z);
				z->p->color = 0;
				z->p->p->color = 1;
				LeftRotate_RB(T,z->p->p);
			}
		}
	}
	T->root->color = 0;
}
void Inorder_RB(RB_Tree *T,Node *x)
{
	if(x != T->nil)
	{
		Inorder_RB(T,x->left);
		printf("%d\t",x->key);
		Inorder_RB(T,x->right);
	}
}
Node *Search_RB(RB_Tree *T,Node *x,int k)
{
	if(x == T->nil || k == x->key)
	{
		return x;
	}
	if(k < x->key)
		return Search_RB(T,x->left,k);
	else
		return Search_RB(T,x->right,k);
}
Node *Minimun_RB(RB_Tree *T,Node *x)
{
	while(x->left != T->nil)
	{
		x = x->left;
	}
	return x;
}
Node *Maximun_RB(RB_Tree *T,Node *x)
{
	while(x->right != T->nil)
	{
		x = x->right;
	}
	return x;
}
Node *Successor_RB(RB_Tree *T,Node *x)
{
	Node *y = (Node *)malloc(sizeof(Node));
	if(x->right != T->nil)
	{
		return Minimun_RB(T,x->right);
	}
	y = x->p;
	while(y != T->nil && x == y->right)
	{
		x = y;
		y = y->p;
	}
	return y;
}
void Transpant_RB(RB_Tree *T,Node *u,Node *v)
{
	if(u->p == T->nil)
		T->root = v;
	else if(u == u->p->left)
		u->p->left = v;
	else 
		u->p->right = v;
	v->p = u->p;
}
void Delete_RB(RB_Tree *T,Node *z)
{
	Node *y = z;
	Node *x = NULL;
	int y_Orig_Color = y->color;
	if(z->left == T->nil)
	{	
		x = z->left;
		Transpant_RB(T,z,z->right);
	}
	else if(z->right == T->nil)
	{
		x = z->left;
		Transpant_RB(T,z,z->left);
	}
	else
	{
		y = Minimun_RB(T,z->right);
		y_Orig_Color = y->color;
		x = y->right;
		if(y->p == z)
		{
			x->p = y;
		}
		else 
		{
			Transpant_RB(T,y,y->right);
			y->right = z->right;
			y->right->p = y;
		}
		Transpant_RB(T,z,y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if(y_Orig_Color == 0)
		DeleteFixUp_RB(T,x);

}
void DeleteFixUp_RB(RB_Tree *T,Node *x)
{
	Node *w = NULL;
	while(x != T->root && x->color == 0)
	{
		if(x == x->p->left)
		{
			w = x->p->right;
			if(w->color == 1)
			{
				w->color = 0;
				x->p->color = 1;
				LeftRotate_RB(T,x->p);
				w = x->p->right;
			}
			if(w->left->color == 0 && w->right->color == 0)
			{
				w->color = 1;
				x = x->p;
			}
			else if(w->right->color == 0)
			{
				w->left->color = 0;
				w->color = 1;
				RightRotate_RB(T,w);
				w = x->p->right;
			}
			w->color = x->p->color;
			x->p->color = 0;
			w->right->color = 0;
			LeftRotate_RB(T,x->p);
			x = T->root;
		}
		else
		{
			w = x->p->left;
			if(w->color == 1)
			{
				w->color = 0;
				x->p->color = 1;
				RightRotate_RB(T,x->p);
				w = x->p->left;
			}
			if(w->left->color == 0 && w->right->color == 0)
			{
				w->color = 1;
				x = x->p;
			}
			else if(w->left->color == 0)
			{
				w->right->color = 0;
				w->color = 1;
				LeftRotate_RB(T,w);
				w = x->p->left;
			}
			w->color = x->p->color;
			x->p->color = 0;
			w->left->color = 0;
			RightRotate_RB(T,x->p);
			x = T->root;
		}
	}
	x->color = 0;
}