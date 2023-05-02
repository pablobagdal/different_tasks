#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
    struct node* parent;
}node;

typedef struct tree{
    struct node* root;
}tree;

typedef struct queue_node{
    struct node* data; 
    struct queue_node* next;
}queue_node;

typedef struct Queue{
    struct queue_node* first;
    struct queue_node* last;
}Queue;

int empty(struct Queue* queue){
    if(queue->first == NULL){
        return 1;
    }
    return 0;
}

void enqueue(struct Queue* queue, struct node* tree_node){ // add to queue
    
    struct queue_node* node = malloc(sizeof(struct queue_node));
    node->data = tree_node;
    node->next = NULL;
    
    if(empty(queue)){
        queue->first = node; // кладем адрес узла
    } else {
        queue->last->next = node;
    }

    queue->last = node;
}

struct node* dequeue(struct Queue* queue){ // remove from queue
    struct node* node = queue->first->data;
    struct queue_node* old_node = queue->first;
    queue->first = queue->first->next; // первый, кто следует за первым
    
    if(empty(queue)){
        queue->last = NULL;
    }
    free(old_node);
    return node;
}

int size(struct Queue* queue){ //считаем размер
    int count = 0;
    struct queue_node* current = queue->first;

    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

struct node* create_node(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void add(struct tree *t, int data){
 struct node* aktualni = t->root;
    if(t->root == NULL){
        t->root = create_node(data);
        return;
    }
    while(aktualni != NULL){
        if(data < aktualni->data){
            if(aktualni->left == NULL){
                aktualni->left = create_node(data);
                aktualni->left->parent = aktualni;
                return;
            }
            aktualni = aktualni->left;
        } else 
        {
            if (aktualni->right == NULL){
                aktualni->right = create_node(data);
                aktualni->right->parent = aktualni;
                return;
            }
            aktualni = aktualni->right;
        }
    }

}


// Найдите минимум и максимум в указанном поддереве (корневом узле): int tree_max(node *root) 
// и int tree_min (node *root). 
// Вы можете предположить, что процедуры никогда не будут вызываться с root = = NULL, 
// т.е. минимум и максимум будут существовать всегда.

int tree_min(struct node* root){
    int min = root->data;
    if(root->left != NULL){
        int left_child = tree_min(root->left);
        if(left_child < min){
            min = left_child;
        }
    }
    if(root->right != NULL){
        int right_child = tree_min(root->right);
        if(right_child < min){
            min = right_child;
        }
    }
    return min;
}
int tree_max(struct node* root){
    int max = root->data;
    if(root->left != NULL){
        int left_child = tree_max(root->left);
        if(left_child > max){
            max = left_child;
        }
    }
    if(root->right != NULL){
        int right_child = tree_max(root->right);
        if(right_child > max){
            max = right_child;
        }
    }
    return max;
}





// Удаление элемента из дерева: int tree_remove (tree *t, int data) 
// возвращает 1, если что-то было удалено, и 0 в противном случае.
void set_left_child (struct node* p, struct node* c){
    p->left = c;
    if(c != NULL) {
        c->parent = p;
    }
}

void set_right_child(struct node* p, struct node* c){
    p->right = c;
    if(c != NULL) {
        c->parent = p;
    }
}

void set_root(struct tree* t, struct node* x){
    t->root = x;
    if(x != NULL){
        x->parent = NULL;
    } 
}
void transplant_tree(struct tree* t, struct node* u, struct node* v){
    if(u->parent == NULL){
        set_root(t, v);
    } else {
        struct node* x = u->parent;
        if( u == x->left){
            set_left_child(x,v);
        } else {
            set_right_child(x,v);
        }
    }
}

void transplant_node(struct tree* t, struct node* u, struct node* v){
    set_left_child(v,u->left);
    set_right_child(v,u->right);
    if(t->root == NULL || u->parent == NULL) {
        set_root(t, v);
    } else {
        struct node* p = u->parent;
        if(u == p->left){
            set_left_child(p,v);
        } else {
            set_right_child(p,v);
        }
    } 
}

// int tree_remove(struct tree* t, int data){
//     struct node* tree_node = t->root;
//     if(tree_node->left == NULL){
//         transplant_tree(t, tree_node, tree_node->right);
//     } else if(tree_node->right == NULL){
//         transplant_tree(t, tree_node, tree_node->left);
//     } else {
//         int min = tree_min(tree_node->right);
//         tree_remove(t , min);
//         transplant_node(t, tree_node, min);
//     }

// }
int tree_remove(struct tree* t, int data){
    struct node* tree_node = t->root;
     while(tree_node != NULL && data != tree_node->data){
        if(data < tree_node->data){
            tree_node = tree_node->left;
        } else {
            tree_node = tree_node->right;
        }
    } 
    if(tree_node == NULL){
        return -1;
    }
    if(tree_node->left == NULL){
        transplant_tree(t, tree_node, tree_node->right);
    } else if(tree_node->right == NULL){
        transplant_tree(t, tree_node, tree_node->left);
    } else {
        int min = tree_min(tree_node->right);
        ///
        struct node* min_node = t->root;
        while(min_node != NULL && min != min_node->data){
            if(data < min_node->data){
                min_node = min_node->left;
            } else {
                min_node = min_node->right;
            }
        } 
        ///
        tree_remove(t , min);
        transplant_node(t, tree_node, min_node);
    }
    return 1;
}

// Перечислите элементы дерева в порядке 
// прохождения по дереву по ширине: void print_bft (tree *t).

void print_bft(struct tree* t){
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->first = NULL;
    queue->last = NULL;
    
    enqueue(queue, t->root);

    while(!empty(queue)){
        struct node* V;
        V = dequeue(queue); // попадает что выкидывает
        printf("%d ", V->data);
        if(V->left != NULL){
            enqueue(queue, V->left );
        }
        if(V->right != NULL){
            enqueue(queue, V->right );
        }

    }
    free(queue);
}






int main(){
    
    struct tree* tree = (struct tree*)malloc(sizeof(struct tree));
    tree->root = NULL;

    add(tree,15);
    add(tree,10);
    add(tree,5);
    add(tree,7);
    add(tree,1);
    add(tree,89);
    int minimum = tree_min(tree->root);
    printf("\nMinimum: %d\n", minimum);
    int maximum = tree_max(tree->root);
    printf("\nMaximum: %d\n", maximum);

    int data_to_delete = 15;
    tree_remove(tree, data_to_delete);
    // if(tree_remove(tree, data_to_delete)){
    //     printf("Strom neobsahuje tento uzel: %i\n", data_to_delete);
    // }

    printf("BFT: ");
    print_bft(tree);


    return 0;
}