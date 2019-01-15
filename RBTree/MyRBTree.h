#pragma once
enum COLOR{black,red};

struct node
{
	int data;
	node* left;
	node* right;
	node* parent;
	COLOR color;
	bool isRED() { return color; }
	node(int val,node * l,node* r,node *p, COLOR c):data(val),left(l),right(r),parent(p),color(c){}

};

typedef node* pnode;

class rbtree
{
private:
	pnode ROOT;
	pnode NIL;
	int size;
	
	
	pnode findmin( pnode T);
	void LeftRotate(pnode  T);
	void RightRotate(pnode T);
	void preorderTraverse0(const pnode & R)const;
	void postorderfree(pnode& R);
public:
	rbtree();
	~rbtree();
	void preorderTraverse() { preorderTraverse0(ROOT->right); }
	int getsize() const { return size; }
	bool contain(int e);
	bool insert(int e);
	bool Delete(int e);


};