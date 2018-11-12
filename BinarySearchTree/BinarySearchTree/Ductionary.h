#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

//判断一个单词是否拼写正确
typedef struct Word{
	char word[20];
	struct Word *left;
	struct Word *right;
}Word;

int WordFind(const Word *root, char word[])
{
	const Word *cur = root;
	int r;

	while(cur != NULL)
	{
		r = strncmp(word, cur->word, 20);
		if(r == 0)
		{
			return 1;
		}
		else if(r > 0)
		{
			cur = cur->right;
		}
		else{
			cur = cur->left;
		}
	}
	return 0;
}

int WordInsert(Word **root, char word[])
{
	int r;
	Word *node;
	if(*root == NULL)
	{
		node = (Word *)malloc(sizeof(Word));
		strncpy(node->word, word, 20);
		node->left = node->right = NULL;
		*root = node;
		return 1;
	}
	r = strncmp(word, (*root)->word, 20);
	if(r == 0)
	{
		return 0;
	}
	if(r < 0)
	{
		return WordInsert(&(*root)->left, word);
	}
	else
	{
		return WordInsert(&(*root)->right, word);
	}
}

int TestDict()
{
	char word[20];
	Word *dict = NULL;

	WordInsert(&dict,"apple");
	WordInsert(&dict,"pear");
	WordInsert(&dict,"water");
	WordInsert(&dict,"sky");
	WordInsert(&dict,"tree");

	while(1){
		scanf("%s",word);
		if(WordFind(dict,word) == 1){
			printf("拼写正确\n");
		}
		else{
			printf("拼写错误\n");
		}
	}
}