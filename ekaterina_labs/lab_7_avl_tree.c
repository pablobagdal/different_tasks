#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	struct node* left;
	struct node* right;
	//struct node(int k) { key = k; left = right = 0; height = 1; }
}node;

struct node* create_node(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

unsigned char height(node* p) // беззнаковый 
{
	return p != NULL ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ){
        return create_node(k);
    }
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}


int main(){

    node* node = create_node(10);
    node->left = create_node(5);
    node->left->left = create_node(3);
    node->right = create_node(15);
    node->left->left->left = create_node(1);
    
    node->height = 4;
    node->left->height = 3;
    node->left->left->height = 2;
    node->right->height = 1;
    node->left->left->left->height = 1;

    node* root = balance(node);
    

}


// node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
// {
// 	return p->left?findmin(p->left):p;
// }

// node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
// {
// 	if( p->left==0 )
// 		return p->right;
// 	p->left = removemin(p->left);
// 	return balance(p);
// }

// node* remove(node* p, int k) // удаление ключа k из дерева p
// {
// 	if( !p ) return 0;
// 	if( k < p->key )
// 		p->left = remove(p->left,k);
// 	else if( k > p->key )
// 		p->right = remove(p->right,k);	
// 	else //  k == p->key 
// 	{
// 		node* q = p->left;
// 		node* r = p->right;
// 		delete p;
// 		if( !r ) return q;
// 		node* min = findmin(r);
// 		min->right = removemin(r);
// 		min->left = q;
// 		return balance(min);
// 	}
// 	return balance(p);
// }