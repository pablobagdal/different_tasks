#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    
    struct Node* left;
    struct Node* right;
    struct Node* parent;

    int bf;
}Node;

typedef struct avl_tree{
    struct Node* root;
}avl_tree;

struct Node* create_node(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->data = data;

    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    node->bf = 0;

    return node;
}

void set_left_child (struct Node* p, struct Node* c){
    p->left = c;
    if(c != NULL) {
        c->parent = p;
    }
}
void set_right_child(struct Node* p, struct Node* c){
    p->right = c;
    if(c != NULL) {
        c->parent = p;
    }
}

struct Node* rotate_left(struct Node* old_root) {
    struct Node* new_root = old_root->right;
    struct Node* B = old_root->left;

    set_right_child(old_root,B);
    set_left_child(new_root,old_root);

    return new_root;
}
struct Node* rotate_right(struct Node* old_root) {
    struct Node* new_root = old_root->left;
    struct Node* B = old_root->right;

    set_left_child(old_root,B);
    set_right_child(new_root,old_root);

    return new_root;
}


void add(struct avl_tree *t, struct Node* added){
    struct Node* current_node = t->root;

    if(t->root == NULL){
        t->root = added;
        return;
    }

    while(current_node != NULL){
        if(added->data < current_node->data){
            if(current_node->left == NULL){
                current_node->left = added;
                current_node->left->parent = current_node;
                return;
            }
            current_node = current_node->left;
        } else 
        {
            if (current_node->right == NULL){
                current_node->right = added;
                current_node->right->parent = current_node;
                return;
            }
            current_node = current_node->right;
        }
    }
}

void avl_insert(struct avl_tree* t, struct Node* added_node) {
    // add just as in binary search tree
    add(t, added_node);

    added_node->bf = 0;

    struct Node*u = added_node->parent;
    struct Node*v = added_node;

    while(u != NULL) {
        if(v == u->left) {
            u->bf++;
        } else {
            u->bf--;
        }

        if(u->bf == 0) {
            // end algorythm
            return;
        } else if(u->bf == 2 || u->bf == -2) {
            struct Node*p = u->parent;

            struct Node*w;
            
            if(u->bf == -2) {
                // справа перевес
                w = rotate_left(u);
            } else {
                w = rotate_right(u);
            }
            
            if(p == NULL) {
                t->root = w;
            } else {
                if(p->left == u) {
                    p->left = w;                    
                } else {
                    p->right = w;
                }
            }

            w->parent = p;

        } else {
            // bf == 1 || bf == -1
            // balance is OK (or not?)
        }

        v = u;
        u = u->parent;

    }

}

int main() {
    avl_tree *tree = malloc(sizeof(avl_tree));
    tree->root = NULL;

    Node*node;
    
    int arr[10] = {1,2,3,4,5,6,7,8,9,0};
    
    for (size_t i = 0; i < sizeof(arr)/sizeof(int); i++)
    {
        node = create_node(arr[i]);
        avl_insert(tree, node);
    }

    printf("The end");
    return 0;
}