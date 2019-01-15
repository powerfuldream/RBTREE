#pragma once
typedef enum { Red, Black } colorType;
typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	colorType color;
}Node, *RBtree;

int Insert(RBtree* T, int argD);
int Delete(RBtree* T, int argD);
int Find(RBtree T, int argD);
int InOredrTraverse(RBtree T);
int PreOredrTraverse(RBtree T);
int Destroy(RBtree* T);