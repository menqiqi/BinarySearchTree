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

//1��ʾ���ҳɹ���0��ʾ����ʧ��
//�ݹ�
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

//�ǵݹ�
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

//����(Ҫ�ı����Ľṹ������Ҫ����ַ���ö���ָ��)
//�ǵݹ�
int BSTreeInsert(BSTreeNode **root, DataType key)
{
	BSTreeNode *parent = NULL;
	BSTreeNode *cur = *root;
	BSTreeNode *node;
	//�ȿ�Ҫ�����Ԫ���Ƿ���ڣ������ڣ�����ʧ��
	while(cur != NULL){
		if(key == cur->key){
			return 0;
		}
		//��¼Ҫ�������һ��λ��
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
	//�����½ڵ�
	node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	node->key = key;
	node->left = node->right = NULL;

	if(parent == NULL)
	{
		//�ڿ����в���
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

//�ݹ�
int BSTreeInsert2(BSTreeNode **root, DataType key)
{
	BSTreeNode *node;
	if(*root == NULL)
	{
		//�����½ڵ�
		node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
		node->key = key;
		node->left = node->right = NULL;

		*root = node;
		return 1;
	}
	if(key == (*root)->key)
	{
		//��Ԫ���Ѿ����ڣ�����ʧ��
		return 0;
	}
	else if(key > (*root)->key)
	{
		return BSTreeInsert2(&(*root)->right, key);//�ǵ�ȡ��ַ
	}
	else
	{
		return BSTreeInsert2(&(*root)->left, key);
	}
}


//�����ӡ
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

//ɾ��
//�ҵ���ɾ���ɹ�������1
//û�ҵ�ɾ��ʧ�ܣ�����0

//ɾ����Ϊ�յ����
static void RemoveLeftNULL(DataType key, BSTreeNode *parent, BSTreeNode **root, BSTreeNode *cur)
{
	if(parent == NULL)
	{
		//Ҫɾ���ľ��Ǹ��ڵ�
		*root = cur->right;
	}
	else{
		if(key < parent->key)
		{
			//cur ��parent��left
			parent->left = cur->right;
		}
		else{
			parent->right = cur->right;
		}
	}
	free(cur);
}

//ɾ����Ϊ�յ����
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

//���Һ��Ӷ���Ϊ��
static void RemoveHasLeftAndRight(BSTreeNode *cur)
{
	//��������������
	//BSTreeNode *del = cur->left;
	//BSTreeNode *delParent = NULL;
	//while(del->right != NULL)
	//{
	//	delParent = del;
	//	del = del->right;
	//}
	////del��������������

	//cur->key = del->key;//��ɾ���ڵ㣬ֻ�ı�ڵ��е�key
	////ɾ��del�ڵ�
	//if(delParent == NULL)
	//{
	//	//���������ľ���cur������
	//	cur->left = del->left;
	//}
	//else{
	//	delParent->right = del->left;
	//}
	//free(del);

	//������������С��
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
		//����������С�ľ���cur���Һ���
		cur->right = del->right;
	}
	else{
		cur->right = delParent->left;
	}
	free(del);
}

int BSTreeNodeRemove(BSTreeNode **root, DataType key)
{
	//�Ȳ��ң���ɾ��
	BSTreeNode *cur = *root;
	BSTreeNode *parent = NULL;
	while(cur != NULL)
	{
		if(key == cur->key)
		{
			//�����ҵ��ˣ���ɾ���ĵط�
			if(cur->left == NULL)
			{
				//curû������
				RemoveLeftNULL(key, parent, root, cur);
			}
			else if(cur->right == NULL)
			{
				//cur û���Һ���
				RemoveRightNULL(key, parent, root, cur);
			}
			else{
				//���Һ��Ӷ���Ϊ��
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



//�ݹ��ɾ��
int BSTreeNodeRemove2(BSTreeNode **root, DataType key)
{
	BSTreeNode *del;
	if(*root == NULL)
	{
		return 0;
	}
	if(key == (*root)->key)
	{
		//�ҵ���
		del = *root;
		if((*root)->left == NULL)
		{
			//1.Ҫɾ�����ǲ��Ǹ�
			//2.Ҫɾ�����Ǹ���������
			*root = (*root)->right;
			free(del);
		}
		else if((*root)->right == NULL)
		{
			*root = (*root)->left;
			free(del);
		}
		else{
			//���Ҷ���Ϊ��
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


//������������ת����һ�������˫������(����������ģ�����Ҫ������)
//��Ҫһ��ǰ��
//ȫ�ֱ���
BSTreeNode *prev = NULL;
void ConnectPrevCurrent(BSTreeNode *current)
{
	if(prev != NULL)
	{
		prev->right = current;
	}
	current->left = prev;
	//��¼ǰ��
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
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,3);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,7);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,1);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,4);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,6);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,8);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,0);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,2);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert(&root,9);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert2(&root,10);
	printf("����%s\n",r?"�ɹ�":"ʧ��");
	r = BSTreeInsert2(&root,2);
	printf("����%s\n",r?"�ɹ�":"ʧ��");

	InOrder2(root);

	InOrder(root);
	printf("\n");
	
	r = BSTreeFind(root,8);
	printf("����8%s\n",r?"�ɹ�":"ʧ��");

	r = BSTreeFind2(root,10);
	printf("����10%s\n",r?"�ɹ�":"ʧ��");

	BSTreeNodeRemove(&root,8);

	r = BSTreeFind(root,8);
	printf("����8%s\n",r?"�ɹ�":"ʧ��");

	BSTreeNodeRemove2(&root,0);

	r = BSTreeFind(root,0);
	printf("����0%s\n",r?"�ɹ�":"ʧ��");
}


