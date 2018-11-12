#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

typedef int DataType;

typedef struct BSTreeNode{
	DataType key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
}BSTreeNode;

//1表示查找成功，0表示查找失败
//递归
int BSTreeFind(const BSTreeNode *root, DataType key)
{
	if(root == NULL)
	{
		return 0;
	}
	if(key == root->key)
	{
		return 1;
	}
	else if(key > root->key)
	{
		return BSTreeFind(root->right, key);
	}
	else
	{
		return BSTreeFind(root->left, key);
	}
}

//非递归
int BSTreeFind2(const BSTreeNode *root, DataType key)
{
	BSTreeNode *cur = (BSTreeNode *)root;
	while(cur != NULL){
		if(key == cur->key){
			return 1;
		}
		else if(key > cur->key){
			cur = cur->right;
		}
		else{
			cur = cur->left;
		}
	}
	return 0;
}

//插入(要改变树的结构，所以要传地址，用二级指针)
//非递归
int BSTreeInsert(BSTreeNode **root, DataType key)
{
	BSTreeNode *parent = NULL;
	BSTreeNode *cur = *root;
	BSTreeNode *node;
	//先看要插入的元素是否存在，若存在，插入失败
	while(cur != NULL){
		if(key == cur->key){
			return 0;
		}
		//记录要插入的上一个位置
		parent = cur;
		if(key > cur->key)
		{
			cur = cur->right;
		}
		else
		{
			cur = cur->left;
		}
	}
	//创建新节点
	node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	node->key = key;
	node->left = node->right = NULL;

	if(parent == NULL)
	{
		//在空树中插入
		*root = node;
		return 1;
	}
	if(key < parent->key)
	{
		parent->left = node;
	}
	if(key > parent->key)
	{
		parent->right = node;
	}
	return 1;
}

//递归
int BSTreeInsert2(BSTreeNode **root, DataType key)
{
	BSTreeNode *node;
	if(*root == NULL)
	{
		//创建新节点
		node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
		node->key = key;
		node->left = node->right = NULL;

		*root = node;
		return 1;
	}
	if(key == (*root)->key)
	{
		//该元素已经存在，插入失败
		return 0;
	}
	else if(key > (*root)->key)
	{
		return BSTreeInsert2(&(*root)->right, key);//记得取地址
	}
	else
	{
		return BSTreeInsert2(&(*root)->left, key);
	}
}


//中序打印
void InOrder(BSTreeNode *root)
{
	if(root == NULL)
	{
		return ;
	}
	InOrder(root->left);
	printf("%d ",root->key);
	InOrder(root->right);
}

//删除
//找到了删除成功，返回1
//没找到删除失败，返回0

//删除左为空的情况
static void RemoveLeftNULL(DataType key, BSTreeNode *parent, BSTreeNode **root, BSTreeNode *cur)
{
	if(parent == NULL)
	{
		//要删除的就是根节点
		*root = cur->right;
	}
	else{
		if(key < parent->key)
		{
			//cur 是parent的left
			parent->left = cur->right;
		}
		else{
			parent->right = cur->right;
		}
	}
	free(cur);
}

//删除右为空的情况
static void RemoveRightNULL(DataType key, BSTreeNode *parent, BSTreeNode **root, BSTreeNode *cur)
{
	if(parent == NULL)
	{
		*root = cur;
	}
	else{
		if(key < parent->key){
			parent->left = cur->left;
		}
		else{
			parent->right = cur->left;
		}
	}
	free(cur);
}

//左右孩子都不为空
static void RemoveHasLeftAndRight(BSTreeNode *cur)
{
	//找左子树中最大的
	//BSTreeNode *del = cur->left;
	//BSTreeNode *delParent = NULL;
	//while(del->right != NULL)
	//{
	//	delParent = del;
	//	del = del->right;
	//}
	////del是左子树中最大的

	//cur->key = del->key;//不删除节点，只改变节点中的key
	////删除del节点
	//if(delParent == NULL)
	//{
	//	//左孩子中最大的就是cur的左孩子
	//	cur->left = del->left;
	//}
	//else{
	//	delParent->right = del->left;
	//}
	//free(del);

	//找右子树中最小的
	BSTreeNode *del = cur->right;
	BSTreeNode *delParent = NULL;
	while(del->left != NULL)
	{
		delParent = del;
		del = del->left;
	}
	cur->key = del->key;
	if(delParent == NULL)
	{
		//右子树中最小的就是cur的右孩子
		cur->right = del->right;
	}
	else{
		cur->right = delParent->left;
	}
	free(del);
}

int BSTreeNodeRemove(BSTreeNode **root, DataType key)
{
	//先查找，后删除
	BSTreeNode *cur = *root;
	BSTreeNode *parent = NULL;
	while(cur != NULL)
	{
		if(key == cur->key)
		{
			//这里找到了，是删除的地方
			if(cur->left == NULL)
			{
				//cur没有左孩子
				RemoveLeftNULL(key, parent, root, cur);
			}
			else if(cur->right == NULL)
			{
				//cur 没有右孩子
				RemoveRightNULL(key, parent, root, cur);
			}
			else{
				//左右孩子都不为空
				RemoveHasLeftAndRight(cur);
			}
			return 1;
		}
		parent = cur;
		if(key < cur->key)
		{
			cur = cur->left;
		}
		else{
			cur = cur->right;
		}
	}
	return 0;
}



//递归的删除
int BSTreeNodeRemove2(BSTreeNode **root, DataType key)
{
	BSTreeNode *del;
	if(*root == NULL)
	{
		return 0;
	}
	if(key == (*root)->key)
	{
		//找到了
		del = *root;
		if((*root)->left == NULL)
		{
			//1.要删除的是不是根
			//2.要删除的是根的左还是右
			*root = (*root)->right;
			free(del);
		}
		else if((*root)->right == NULL)
		{
			*root = (*root)->left;
			free(del);
		}
		else{
			//左右都不为空
			RemoveHasLeftAndRight(*root);
		}
		return 1;
	}
	if(key < (*root)->key)
	{
		return BSTreeNodeRemove2(&(*root)->left, key);
	}
	else{
		return BSTreeNodeRemove2(&(*root)->right, key);
	}
}


//将二叉搜索树转换成一个排序的双向链表(中序是有序的，所以要用中序)
//需要一个前驱
//全局变量
BSTreeNode *prev = NULL;
void ConnectPrevCurrent(BSTreeNode *current)
{
	if(prev != NULL)
	{
		prev->right = current;
	}
	current->left = prev;
	//记录前驱
	prev = current;
}



void InOrder2(BSTreeNode *root)
{
	if(root == NULL)
	{
		return;
	}
	InOrder2(root->left);
	ConnectPrevCurrent(root);
	InOrder2(root->right);
}


void Test()
{
	BSTreeNode *root = NULL;
	int r;
	r = BSTreeInsert(&root,5);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,3);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,7);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,1);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,4);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,6);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,8);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,0);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,2);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert(&root,9);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert2(&root,10);
	printf("插入%s\n",r?"成功":"失败");
	r = BSTreeInsert2(&root,2);
	printf("插入%s\n",r?"成功":"失败");

	InOrder2(root);

	InOrder(root);
	printf("\n");
	
	r = BSTreeFind(root,8);
	printf("查找8%s\n",r?"成功":"失败");

	r = BSTreeFind2(root,10);
	printf("查找10%s\n",r?"成功":"失败");

	BSTreeNodeRemove(&root,8);

	r = BSTreeFind(root,8);
	printf("查找8%s\n",r?"成功":"失败");

	BSTreeNodeRemove2(&root,0);

	r = BSTreeFind(root,0);
	printf("查找0%s\n",r?"成功":"失败");
}


