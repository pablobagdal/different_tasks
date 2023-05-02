#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>

// Реализуйте структуру для B-дерева.
// Реализуйте поиск элементов в B-дереве.
// Реализуйте встраивание в B-дерево.

const int t = 2;


typedef struct Node{
    int keys[2*t-1];
    struct Node* children[2*t];// элементы массива указатели
    struct Node* parent;
    int n;
    bool leaf; //leaf true/false 
}Node;

Node* create_node(){
    Node* node = malloc(sizeof(Node));
    // node->keys[0] = t;// = malloc(sizeof(int)*(2*t-1)); // возьми 4 (2*t-1) [****][****].... keys хранит адрес первого из них
    for (size_t i = 0; i < 2*t-1; i++)
    {
        node->keys[i] = 0;
    }
    // int - 4 байт
    // 1 байт = 8 бит
    
    //node->children = malloc(sizeof(Node*)*(2*t));
    for(int i = 0; i < 2*t; i++){ // чтобы все указатели были в null
        node->children[i] = NULL;
    }
    node->parent = NULL;

    node->n = 0;

    node->leaf = true;

    return node;
}

typedef struct BTree{
    struct Node* root;
}BTree;

BTree* create_tree(){
    BTree* tree = malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

Node* search(struct Node* node, int data, int* result_index){
    int i = 0;
    while(i < node->n && data > node->keys[i]){
        i++;
    }
    if( i < node->n && data == node->keys[i]){
        *result_index = i;
        return node;
    } else if (node->leaf){
        //*result_index = 0;
        return NULL; 
    } else {
        return search(node->children[i], data, result_index); //
    }
}


Node* find_insertion_node(Node* x, int data){
    int i = 0;
    while(i < x->n && data > x->keys[i]){
        i++;
    }
    if(x->leaf){
        return x;
    } else {
        return find_insertion_node(x->children[i], data);
    }
}

void shift_right(struct Node* x, int i){
    x->children[x->n] = x->children[x->n - 1];
    for(int j = x->n - 1; j > i; j--){
        x->keys[j] = x->keys[j-1];
        x->children[j] = x->children[j-1];
    }
}

void set_as_child(struct Node* x, int i, struct Node* y){
    x->children[i] = y;
    if(y != NULL){
        y->parent = x;
    }
}

void split_node(Node *x, int* median, Node* left, Node* right){
    Node* z = create_node();
    z->leaf = x->leaf;
    z->n = t-1;

    for(int j = 0; j < t-1; j++){
        z->keys[j] = x->keys[t+j];
        z->children[j] = x->children[t+j];
    }
    z->children[t-1] = x->children[2*t-1];

    x->n = t-1;

    *median = x->keys[t-1];
    *left = *x;
    *right = *z;
}

void insert_with_subtrees(BTree* tree, Node* x, int data, Node* left, Node* right){
    if(x == NULL){

        Node* z = create_node();
        z->keys[0] = data;
        z->leaf = false;
        z->n = 1;
        z->parent = NULL;

        set_as_child(z, 0, left);
        set_as_child(z, 1, right);

        tree->root = z;
    } else if (x->n == 2*t-1){
        Node* p = x->parent;
        // int* m_ptr;
        
        int up_key = 0;
        Node* l = create_node();
        Node* r = create_node();

        split_node(x, &up_key, l, r);
        // int up_key = *m_ptr;

        if(data < up_key){
            insert_with_subtrees(tree, l, data, left, right);
        } else {
            insert_with_subtrees(tree, r, data, left, right);
        }
        insert_with_subtrees(tree, p, up_key, l, r);
    } else {
        int i = 0;
        while(i < x->n && data > x->keys[i]){
            i++;
        }
        shift_right(x,i);
        x->keys[i] = data;
        x->n = x->n + 1;
        set_as_child(x ,i, left);
        set_as_child(x ,i + 1, right);
    }
}

void tree_insert (struct BTree* tree, int data){
    Node* target = find_insertion_node(tree->root, data);
    insert_with_subtrees(tree, target, data, NULL, NULL);
}

BTree* empty_tree(){
    struct BTree* tree = create_tree();
    tree->root = create_node();
    tree->root->n = 0;
    tree->root->leaf = true;
    tree->root->parent = NULL;
    return tree;
}

int main(){

    BTree* tree = empty_tree();

    tree_insert(tree, 1);
    tree_insert(tree, 2);
    tree_insert(tree, 3);
    tree_insert(tree, 4);
    tree_insert(tree, 5);
    tree_insert(tree, 6);
    tree_insert(tree, 7);
    tree_insert(tree, 8);
    tree_insert(tree, 9);
    tree_insert(tree, 10);

    int* ptr = malloc(sizeof(int));

    Node* result = search(tree->root, 10, ptr);

    if(result == NULL) {
        printf("Value is not found\n");
    } else {
        printf("Result = %i\n", result->keys[*ptr]);
    }

    return 0;
}






