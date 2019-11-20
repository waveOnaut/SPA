#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct treeNode
{
	int data;
	struct treeNode* left;
	struct treeNode* right;
	
}treeNode;



treeNode *createNode(int data)
{
	treeNode *new = (treeNode*)malloc(sizeof(treeNode));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}


void insertTreeNode(treeNode **root, int data)
{
	if(*root == NULL)
	{
		(*root) = createNode(data);
		return;
	}

	if(data < (*root)->data)
		insertTreeNode(&((*root)->left), data);
	else
		insertTreeNode(&((*root)->right), data);

}


int search(treeNode *root_ref, int data)
{
	if(root_ref == NULL)
    	return 0;
	else if(root_ref->data == data) 
		return 1;
	else if(root_ref->data  > data ) 
		return search(root_ref->left, data);
	else
		return search(root_ref->right, data);
}

void inOrder(treeNode *root_ref)
{
	if(root_ref == NULL)
		return;


	inOrder(root_ref ->left); 
	printf("%i \n",root_ref->data);
	inOrder(root_ref -> right);
}



treeNode *minNode(treeNode *root_ref)
{
	if(root_ref->left == NULL )
	 return root_ref;

	return minNode(root_ref->left);	

}

int countLeaves(treeNode *root_ref)
{
	if(root_ref == NULL)
		return 0;
	if(root_ref->left == NULL && root_ref->right == NULL)
		return 1;
	else
		return countLeaves(root_ref->left)
				+ countLeaves(root_ref->right);
}

int countInnerNodes(treeNode *root_ref)
{
	if(root_ref == NULL || (root_ref->left == NULL &&
						root_ref->right == NULL))
		return 0;

	return 1 + countInnerNodes(root_ref->left)
			 + countInnerNodes(root_ref->right);

}

unsigned int countNodes(treeNode *root_ref)
{

	if(root_ref == NULL)
		return 0; 

	return( 1 + countNodes(root_ref->left) + countNodes(root_ref->right));
}


bool isBSTUtil(node *root, int min, int max)
{
	if(root == NULL)
		return true;

	if(root->data < min || root->data > max)
		return false;


	return (isBSTUtil(root->left, min, root->data -1 ) &&
			isBSTUtil(root->right, root->data+1, max));
}

bool isBST(node *root)
{
	return isBSTUtil(root, INT_MIN, INT_MAX);
}
void deleteNode(treeNode** root, int v)
{
	treeNode *temp;
	temp = (*root);
	if(*root == NULL)
		return;
	if(v < (*root)->data)
		deleteNode(&((*root)->left), v);
	else if(v > (*root)->data)
		deleteNode(&((*root)->right), v);
	else
	{
		if((*root)->left != NULL && (*root)->right != NULL)
		{
			temp = minNode((*root)->right);
			(*root)->data = temp->data;
			deleteNode(&((*root)->right), (*root)->data);
		}
		else
		{
			if((*root)->right == NULL)
				(*root) = (*root)->left;
			if((*root)->left == NULL)
				(*root) = (*root)->right;
		}
	}

	return;
}


void _deleteTree(treeNode *root_ref)
{
	if(root_ref->left)
	{
		_deleteTree(root_ref->left);
		free(root_ref->left);
	}
	if(root_ref->right)
	{	
		_deleteTree(root_ref->right);
		free(root_ref->right);
	}
}


void deleteTree(treeNode **root)
{
	if(*root)
	{
		_deleteTree(*root);
		free(*root);
	}
}


typedef struct _stack
{
	struct treeNode *node;
	struct _stack *next;
}stack;

stack *createStack(){ return NULL;}

stack *push(stack *head, treeNode *v)
{
	stack *tmp = (stack *)malloc(sizeof(stack*));
	tmp->node = v;
	tmp->next = head;
	head = tmp;
	return head;
}

stack *pop(stack *head, treeNode **element)
{
	stack *tmp = head;
	*element = tmp->node;
 	head = tmp->next;
 	free(tmp);
 	return head;
}

treeNode *top(stack *head)
{
 return head->node;
}



int exist(treeNode *root, int  v)
{
	stack *left, *right;
	treeNode *tmp = root;
	
	left = createStack(); 
	right = createStack();

	while(tmp != NULL)
	{
		left = push(left,tmp);
		tmp = tmp->left;
	}

	tmp = root;

	while(tmp != NULL)
	{
		right = push(right,tmp);
		tmp = tmp->right;
	}


	while(top(left)->data != top(right)->data)
	{
		int v1 = top(left)->data;
		int v2 = top(right)->data;
		
		if(v1 + v2 == v)
			return 1;
		else if( v < (v1+v2))
		{
			right = pop(right,&tmp);
			if(tmp->left != NULL)
			{	
				tmp = tmp->left;

				while(tmp != NULL)
				{
					right = push(right, tmp);
					tmp = tmp->right;
				}

			}
		}
		else
		{
			left = pop(left,&tmp);
			if(tmp->right != NULL)
			{
				tmp = tmp->right;
				
				while(tmp != NULL)
				{
					left = push(left, tmp);
					tmp = tmp->left;
				}
			}

		}


	}
}


int main()
{

	treeNode *root = NULL;
	insertTreeNode(&root, 35);
	insertTreeNode(&root, 25);
	insertTreeNode(&root, 15);
	insertTreeNode(&root, 30);
	insertTreeNode(&root, 50);
	insertTreeNode(&root, 40);


	inOrder(root);

	isBST(root) ? printf("Da\n") : printf("NE"); 

	if(exist(root,55))
		printf("Da\n");
	else
		printf("Ne\n");


	deleteTree(&root);

return 0;
}