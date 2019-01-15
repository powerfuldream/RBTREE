#include "stdafx.h"
#include "MyRBTree.h"
#include <limits.h>
pnode rbtree::findmin(pnode T)
{
	while (T->left!=NIL)
	{
		T = T->left;
	}
	return T;
}

void rbtree::LeftRotate(pnode T)
{
	pnode P = T->parent;
	pnode R = T->right;
	if (P->left == T)
		P->left = R;
	else
		P->right = R;
	R->parent = P;

	T->right = R->left;
	if (R->left)
		R->left->parent = T;

	R->left = T;
	T->parent = R;

}

void rbtree::RightRotate(pnode T)
{
	pnode P = T->parent;
	pnode L = T->left;
	if (P->left == T)
		P->left = L;
	else
		P->right = L;
	L->parent = P;

	T->left = L->right;
	if (L->right)
		L->right->parent = T;
	
	L->right = T;
	T->parent = L;



}

rbtree::rbtree()
{
	ROOT = new node(INT_MIN, nullptr, nullptr, nullptr, black);
	NIL = new node(0, nullptr, nullptr, nullptr, black);
	ROOT->left = NIL;
	ROOT->right = NIL;
	ROOT->parent = ROOT;

	NIL->left = NIL->right = NIL;
	NIL->parent = ROOT;
	size = 0;
}

bool rbtree::contain(int e)
{
	pnode T = ROOT->right;
	while (T!=NIL)
	{
		if (e > T->data)
			T = T->right;
		else if (e < T->data)
			T = T->left;
		else
			return true;
	}
	return false;
	

}

bool rbtree::insert(int e)
{
	pnode P = ROOT;
	pnode X = ROOT->right;
	while (X != NIL)
	{
		if (e < X->data)
		{
			P = X;
			X = X->left;
		}
			
		else if (e > X->data)
		{
			P = X;
			X = X->right;
		}
		else
			return false;
	}
	X = new node(e, NIL, NIL, P, red);
	if (e >= P->data)
		P->right = X;
	else
		P->left = X;

	while (true)
	{
		P = X->parent;
		if (P->isRED())//ºì¸¸
		{
			pnode G = P->parent;//Ò¯Ò¯½Úµã
			pnode U;//¸¸½ÚµãµÄÐÖµÜ½Úµã
			if (P->left == X)
				 U = P->right;
			else
				 U = P->left;
			if (U->isRED())//Êå¸¸ºìÉ«
			{
				P->color = black;
				U->color = black;
				G->color = red;
				X = G;
			}
			else//ºì¸¸ºÚÊå
			{
				if (G->left == P)
				{
					if (P->left == X)
					{
						RightRotate(G);
						P->color = black;
						G->color = red;
						break;
					}
					else
					{
						LeftRotate(P);
						RightRotate(G);
						X->color = black;
						G->color = red;
						break;
					}
				}
				else
				{
					if (P->right == X)
					{
						LeftRotate(G);
						P->color = black;
						G->color = red;
						break;
					}
					else
					{
						RightRotate(P);
						LeftRotate(G);
						X->color = black;
						G->color = red;
						break;
					}
				}

			}
		}
		else//ºÚ¸¸
			break;
	}
	++size;
	ROOT->right->color = black;
	return true;
}

bool rbtree::Delete(int e)
{
	
}
