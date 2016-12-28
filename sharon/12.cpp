/*--------2016.12.28----------*
*-introduction to algorithms-*
*-----------12------------*
*-----BINARY SORT TREE------*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int key;
	Node *p;
	Node *left;
	Node *right;
}Node;
typedef struct{
	Node *root;
}TreeRoot;

void Create_BST(TreeRoot *T,int *data,int len);
Node *Search_BST(Node *x,int k);
Node *Minimun_BST(Node *x);
Node *Maximun_BST(Node *x);
Node *Successor_BST(Node *x);
void Inorder_BST(Node *x);
void Insert_BST(TreeRoot *T,Node *z);
void Transpant_BST(TreeRoot *T,Node *u,Node *v);
void Delete_BST(TreeRoot *T,Node *z);

int main()
{
	int data[] = {6,2,5,7,5,8};
	int len = sizeof(data)/sizeof(data[0]);
	int i;
	TreeRoot *T = (TreeRoot *)malloc(sizeof(TreeRoot));
	T->root = NULL;
	Create_BST(T,data,len);
	printf("Binary Sort Tree Elements:\n");
	Inorder_BST(T->root);
	printf("\n");
	
	int k = 5;
	Node *result = (Node *)malloc(sizeof(Node));
	printf("------Testing Search_BST.search elements k = %d-----\n",k);
	result = Search_BST(T->root,k);
	printf("The result of search elements %d:\n",result->key);
	
	result = Minimun_BST(T->root);
	printf("Minimum elements:%d\n",result->key);
	
	result = Maximun_BST(T->root);
	printf("Maximum elements:%d\n",result->key);
	
	result = Successor_BST(T->root);
	printf("Successor elements:%d\n",result->key);
	 
 	printf("------Testing Delete_BST------\n");
 	printf("Delete tree root:\n");
 	Delete_BST(T,T->root);
	printf("Binary Sort Tree Elements:\n");
	Inorder_BST(T->root);
	printf("\n");
	
	free(result);
	free(T);
	return 0;
}
void Create_BST(TreeRoot *T,int *data,int len)
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
			z->p = NULL;
			z->left = NULL;
			z->right = NULL;
			Insert_BST(T,z);	
		}
		
	}
	return;
}
void Insert_BST(TreeRoot *T,Node *z)
{
	Node *y = NULL;
	Node *x = T->root;
	while(x != NULL)
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
	if(y == NULL)
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
}
void Inorder_BST(Node *x)
{
	if(x != NULL)
	{
		Inorder_BST(x->left);
		printf("%d\t",x->key);
		Inorder_BST(x->right);
	}
}
Node *Search_BST(Node *x,int k)
{
	if(x == NULL || k == x->key)
	{
		return x;
	}
	if(k < x->key)
		return Search_BST(x->left,k);
	else
		return Search_BST(x->right,k);
}
Node *Minimun_BST(Node *x)
{
	while(x->left != NULL)
	{
		x = x->left;
	}
	return x;
}
Node *Maximun_BST(Node *x)
{
	while(x->right != NULL)
	{
		x = x->right;
	}
	return x;
}
Node *Successor_BST(Node *x)
{
	Node *y = (Node *)malloc(sizeof(Node));
	if(x->right != NULL)
	{
		return Minimun_BST(x->right);
	}
	y = x->p;
	while(y != NULL && x == y->right)
	{
		x = y;
		y = y->p;
	}
	return y;
}
void Transpant_BST(TreeRoot *T,Node *u,Node *v)
{
	if(u->p == NULL)
		T->root = v;
	else if(u == u->p->left)
		u->p->left = v;
	else 
		u->p->right = v;
	if(v != NULL)
		v->p = u->p;
}
void Delete_BST(TreeRoot *T,Node *z)
{
	Node *y = (Node *)malloc(sizeof(Node));
	if(z->left == NULL)
	{
		Transpant_BST(T,z,z->right);
	}
	else if(z->right == NULL)
	{
		Transpant_BST(T,z,z->left);
	}
	else
	{
		y = Minimun_BST(z->right);
		if(y->p != z)
		{
			Transpant_BST(T,y,y->right);
			y->right = z->right;
			y->right->p = y;
		}
		Transpant_BST(T,z,y);
		y->left = z->left;
		y->left->p= y;
	}

}