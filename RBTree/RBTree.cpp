#include "stdafx.h"
#include "RBtree.h"
#include<limits.h>
#include <stdlib.h>
#include <stdio.h>

static int Init(RBtree* T);
static int FindMin(Node* ptr, RBtree NullNode);
static void RightRotate(RBtree* T);
static void LeftRotate(RBtree* T);

static void RightPreOrderTra(RBtree ptr, RBtree NullNode);
static void RightInOrderTra(RBtree ptr, RBtree NullNode);
static void RightPostOrderTra(RBtree ptr, RBtree NullNode);

int Insert(RBtree* T, int argD) {
	Node *X, *P, *GP, *GGP, *NullNode;
	Node **tmp;
	if (T == NULL) {
		return -1;
	}

	if (*T == NULL) {
		if (Init(T) == -1) {
			return -1;
		}
	}

	GP = NULL;
	GGP = NULL;
	P = NULL;
	X = (*T);//从头结点开始，防止插入负无穷
	NullNode = (*T)->left;
	NullNode->data = argD;

	while (X->data != argD) {
		if (X->left->color == Red && X->right->color == Red) {
			X->color = Red;
			X->left->color = Black;
			X->right->color = Black;

			if (P->color == Red) {
				if (argD > GGP->data) {
					tmp = &(GGP->right);
				}
				else {
					tmp = &(GGP->left);
				}

				if (argD > GP->data) {
					if (argD > P->data) {
						LeftRotate(tmp);
						P->color = Black;
						GP->color = Red;
						GP = GGP; //为能够正确下落一层做保证
					}
					else {
						RightRotate(&(GP->right));
						LeftRotate(tmp);
						X->color = Black;
						GP->color = Red;
						P = X;//为能够正确下落一层做保证
						GP = P;//为能够正确下落一层做保证
					}
				}
				else {
					if (argD < P->data) {
						RightRotate(tmp);
						P->color = Black;
						GP->color = Red;
						GP = GGP;
					}
					else {
						LeftRotate(&(GP->left));
						RightRotate(tmp);
						X->color = Black;
						GP->color = Red;
						P = X;
						GP = P;
					}
				}
			}
		}

		GGP = GP; GP = P; P = X;
		if (argD > X->data) {
			X = X->right;
		}
		else {
			X = X->left;
		}

	}

	if (X != NullNode) {
		(*T)->right->color = Black;
		return -1;
	}

	X = (Node*)malloc(sizeof(Node));
	if (X == NULL) {
		(*T)->right->color = Black;
		return -1;
	}

	X->color = Red;
	X->data = argD;
	X->left = X->right = NullNode;
	if (argD > P->data) {
		P->right = X;
	}
	else {
		P->left = X;
	}

	if (P->color == Red) {
		if (argD > GGP->data) {
			tmp = &(GGP->right);
		}
		else {
			tmp = &(GGP->left);
		}

		if (argD > GP->data) {
			if (argD > P->data) {
				LeftRotate(tmp);
				P->color = Black;
				GP->color = Red;
				GP = GGP;
			}
			else {
				RightRotate(&(GP->right));
				LeftRotate(tmp);
				X->color = Black;
				GP->color = Red;
				P = X;
				GP = P;
			}
		}
		else {
			if (argD < P->data) {
				RightRotate(tmp);
				P->color = Black;
				GP->color = Red;
				GP = GGP;
			}
			else {
				LeftRotate(&(GP->left));
				RightRotate(tmp);
				X->color = Black;
				GP->color = Red;
				P = X;
				GP = P;
			}
		}
	}

	(*T)->right->color = Black;
	return 0;
}

int Delete(RBtree* T, int argD) {
	Node *X, *B, *P, *GP, *NullNode;
	RBtree *tmp;
	if (T == NULL || *T == NULL) {
		return -1;
	}

	P = *T;
	X = (*T)->right;//X从root开始，防止删除负无穷
	NullNode = (*T)->left;
	B = NullNode;
	GP = NULL;
	(*T)->right->color = Red;//根涂红

	while (1) {
		if (X == NullNode) {
			(*T)->right->color = Black;
			return -1;//删除元素不存在
		}

		if (X->color == Black) {
			if (X->left->color == Black && X->right->color == Black) {
				if (B->color == Red) {
					if (GP->right == P) {
						tmp = &(GP->right);
					}
					else {
						tmp = &(GP->left);
					}

					B->color = Black;
					P->color = Red;
					if (P->right == X) {
						RightRotate(tmp);
						B = P->left;
						GP = *tmp;
					}
					else {
						LeftRotate(tmp);
						B = P->right;
						GP = *tmp;
					}
				}

				if (B->color == Black) {
					if (B->left->color == Black && B->right->color == Black) {
						P->color = Black;
						X->color = Red;
						B->color = Red;
					}
					else {
						if (GP->right == P) {
							tmp = &(GP->right);
						}
						else {
							tmp = &(GP->left);
						}

						if (P->right == X) {
							if (B->left->color == Red) {
								P->color = Black;
								X->color = Red;
								B->color = Red;
								B->left->color = Black;
								RightRotate(tmp);
							}
							else
								if (B->right->color == Red) {
									P->color = Black;
									X->color = Red;
									LeftRotate(&(P->left));
									RightRotate(tmp);
								}
						}
						else {
							if (B->right->color == Red) {
								P->color = Black;
								X->color = Red;
								B->color = Red;
								B->right->color = Black;
								LeftRotate(tmp);
							}
							else
								if (B->left->color == Red) {
									P->color = Black;
									X->color = Red;
									RightRotate(&(P->right));
									LeftRotate(tmp);
								}
						}
					}
				}
			}
		}

		if (X->data == argD) {
			if (X->left != NullNode && X->right != NullNode) {
				argD = FindMin(X->right, (*T)->left);
				X->data = argD;
				GP = P;
				P = X;
				X = P->right;
				B = P->left;
			}
			else
				if (X->left == NullNode && X->right == NullNode) {
					if (P->right == X) {
						P->right = NullNode;
					}
					else {
						P->left = NullNode;
					}
					free(X);

					if ((*T)->left == NullNode && (*T)->right == NullNode) {
						free(NullNode);
						free(*T);
						*T = NULL;
						return 0;
					}
					(*T)->right->color = Black;
					return 0;
				}
				else
					if (X->left != NullNode) {
						X->data = X->left->data;
						free(X->left);
						X->left = NullNode;
						(*T)->right->color = Black;
						return 0;
					}
					else
						if (X->right != NullNode) {
							X->data = X->right->data;
							free(X->right);
							X->right = NullNode;
							(*T)->right->color = Black;
							return 0;
						}
		}
		else
			if (argD > X->data) {
				GP = P;
				P = X;
				X = P->right;
				B = P->left;
			}
			else
				if (argD < X->data) {
					GP = P;
					P = X;
					X = P->left;
					B = P->right;
				}
	}
}

int Find(RBtree T, int argD) {
	if (T != NULL) {
		Node* root = T->right;
		Node* NullNode = T->left;
		while (root != NullNode) {
			if (root->data == argD) {
				return 0;
			}
			else
				if (argD > root->data) {
					root = root->right;
				}
				else {
					root = root->left;
				}
		}
	}
	return -1;

}

int InOredrTraverse(RBtree T) {
	if (T == NULL) {
		return -1;
	}
	RightInOrderTra(T->right, T->left);
	return 0;
}

int PreOredrTraverse(RBtree T) {
	if (T == NULL) {
		return -1;
	}
	RightPreOrderTra(T->right, T->left);
	return 0;
}

int Destroy(RBtree* T) {
	if (*T == NULL) {
		return -1;
	}
	RightPostOrderTra((*T)->right, (*T)->left);
	free((*T)->left);
	free((*T));
	*T = NULL;
	return 0;
}

static void RightInOrderTra(RBtree ptr, RBtree NullNode) {
	if (ptr != NullNode) {
		RightInOrderTra(ptr->left, NullNode);
		printf("% 3d", ptr->data);
		RightInOrderTra(ptr->right, NullNode);
	}
}

static void RightPreOrderTra(RBtree ptr, RBtree NullNode) {
	if (ptr != NullNode) {
		printf("%3d:%c(%3d,%3d)\n",
			ptr->data, ptr->color == Red ? 'R' : 'B',
			ptr->left == NullNode ? -1 : ptr->left->data,
			ptr->right == NullNode ? -1 : ptr->right->data
		);
		RightPreOrderTra(ptr->left, NullNode);
		RightPreOrderTra(ptr->right, NullNode);
	}
}

static void RightPostOrderTra(RBtree ptr, RBtree NullNode) {
	if (ptr != NullNode) {
		RightPostOrderTra(ptr->left, NullNode);
		RightPostOrderTra(ptr->right, NullNode);
		free(ptr);
	}
}

static int Init(RBtree* T) {
	Node* tmp;
	tmp = (Node*)malloc(sizeof(Node));
	*T = (Node*)malloc(sizeof(Node));
	if (*T == NULL || tmp == NULL) {
		return -1;
	}
	(*T)->data = INT_MIN;
	(*T)->color = Black;
	(*T)->left = (*T)->right = tmp;
	tmp->color = Black;
	tmp->left = tmp->right = tmp;
	return 0;
}

static void RightRotate(RBtree* T) {
	Node* Parent = (*T);
	Node* LeftSon = (*T)->left;
	Parent->left = LeftSon->right;
	LeftSon->right = Parent;
	*T = LeftSon;
}

static void LeftRotate(RBtree* T) {
	Node* Parent = (*T);
	Node* RightSon = (*T)->right;
	Parent->right = RightSon->left;
	RightSon->left = Parent;
	*T = RightSon;
}
static int FindMin(Node* ptr, RBtree NullNode) {
	while (ptr->left != NullNode) {
		ptr = ptr->left;
	}
	return ptr->data;
}