#include<stdio.h>
#include<string.h>
#include <stdlib.h>

// Реализовать соответствующие структуры для двоичного дерева поиска
// (узел дерева node; дерево tree - содержит указатель на корень).
// Дерево будет содержать значения int.


typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

typedef struct tree{
    struct node* koren;
}tree;

struct node* create_node(int data){ // функция для создания нового узла
    struct node* node = (struct node* )malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//добавление элемента в дерево void add(tree *t, int data)
void add(struct tree *t, int data){
    struct node* aktualni = t->koren;
    if(t->koren == NULL){
        t->koren = create_node(data);
        return;
    }
    while(aktualni != NULL){
        if(data < aktualni->data){
            if(aktualni->left == NULL){
                aktualni->left = create_node(data);
                return;
            }
            aktualni = aktualni->left;
        } else 
        {
            if (aktualni->right == NULL){
                aktualni->right = create_node(data);
                return;
            }
            aktualni = aktualni->right;
        }
    }

}


// перечислите элементы в дереве в порядке возрастания 
// void print_in_order(tree t)

void LKP(struct node* node){
    if(node->left != NULL){
        LKP(node->left);
    }
    printf("%d ", node->data);
    if(node->right != NULL){
        LKP(node->right);
    }
}

void print_in_order(struct tree t){
    LKP(t.koren);
}

//вычисление глубины дерева int depth (tree t)
int get_depth(node* node, int current_depth) {
    int max_depth = current_depth;

    int left_child = 0;
    int right_child = 0;

    if(node->left != NULL) {
        left_child = get_depth(node->left, current_depth+1);
    }

    if(node->right != NULL) {
        right_child = get_depth(node->right, current_depth+1);
    } 
    
    if(left_child > max_depth) {
        max_depth = left_child;
    }
    if(right_child > max_depth) {
        max_depth = right_child;
    }

    return max_depth;
}
int depth (tree t){
    if(t.koren == NULL)
    { 
        return 0;
    }

    int tree_depth = get_depth(t.koren, 1);

    return tree_depth;
}

int main(){
    
    struct tree* tree = (struct tree*)malloc(sizeof(struct tree));
    tree->koren = NULL;

    add(tree,5);
    add(tree,8);
    add(tree,-12);
    add(tree,56);
    add(tree,1);
    add(tree,5);
    add(tree,8);
    add(tree,-12);
    add(tree,56);
    add(tree,1);
    
    print_in_order(*tree);
   
    int tree_depth = depth(*tree);

    printf("\nDepth: %i\n", tree_depth);







    return 0;
}