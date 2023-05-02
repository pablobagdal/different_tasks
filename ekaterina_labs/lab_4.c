#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <assert.h>
#include<time.h>

// Создайте структуру для узла m-árního дерева  и 
//тип tree_node для этой структуры. Выберите представление массивом 
//или списком.


typedef struct tree_node{
    int data;
    struct tree_node* child;
    struct tree_node* sibling;
}tree_node; 


// Создайте структуру для корня m-árního дерева и тип tree 
// для этой структуры.

typedef struct tree{
    struct tree_node* koren;
    int number_children;
}tree; 

typedef struct Node{
    struct tree_node* data; 
    struct Node* next;
}Node;

typedef struct Queue{
    struct Node* first;
    struct Node* last;
}Queue;

int empty(struct Queue* queue){
    if(queue->first == NULL){
        return 1;
    }
    return 0;
}

void enqueue(struct Queue* queue, struct tree_node* tree_node){ // add to queue
    struct Node* node = malloc(sizeof(struct Node));
    node->data = tree_node;
    node->next = NULL;
    
    if(empty(queue)){
        queue->first = node; // кладем адрес узла
    } else {
        queue->last->next = node;
    }

    queue->last = node;
}

struct tree_node* dequeue(struct Queue* queue){ // remove from queue
    struct tree_node* node = queue->first->data;
    
    queue->first = queue->first->next; // первый, кто следует за первым
    
    if(empty(queue)){
        queue->last = NULL;
    }

    return node;
}

int size(struct Queue* queue){ //считаем размер
    int count = 0;
    struct Node* current = queue->first;

    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

// 1 - добавьте элемент в дерево void add (tree *t, int data). 
//Выберите, где вы хотите добавить элемент в дерево (например, случайным образом). 
//Но результатом все равно должно быть m-дерево.

struct tree_node* create_node(int data){
    struct tree_node* node = (struct tree_node* )malloc(sizeof(struct tree_node));
    node->data = data;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

void add(struct tree *t, int data){
   

    int random = rand()%2; // 0 or 1

    int current_siblings_counter = 1; 

     if( t->koren == NULL){ // если дерево пустое
        t->koren = create_node(data);
        return;
    } 
    
    struct tree_node* prev_node = t->koren;
    struct tree_node* current_node = prev_node->child;

    int is_siblings = 0;
     
    while (current_node != NULL){
        prev_node = current_node;

        if(rand()%2 == 1 || current_siblings_counter == t->number_children){
            current_node = current_node->child;
            is_siblings = 0;
            current_siblings_counter = 1;
        } else {
            current_node = current_node->sibling;
            is_siblings = 1;

            current_siblings_counter++;
        }
    }

    current_node = create_node(data);

    if(is_siblings){
        prev_node->sibling = current_node;
    } else {
        prev_node->child = current_node;
    }    
}


// 2 - выписывание элементов в дереве прохождением вглубь 
//void dfs_print(tree t)

void dfs_print(struct tree_node* node){
    if( node == NULL){
        return;
    }
    printf("%d ", node->data);
    dfs_print(node->child);
    dfs_print(node->sibling);
}



// 3 - выписывание элементов в дереве прохождением по ширине 
void bfs_print(struct tree* t){
    struct Queue *queue = malloc(sizeof(struct Queue));
    queue->first = NULL;
    queue->last = NULL;
    
    enqueue(queue, t->koren);

    while(!empty(queue)){
        struct tree_node *V;
        V = dequeue(queue);
        printf("%d ", V->data);
        
        for(struct tree_node* cur = V->child; cur != NULL; cur = cur->sibling){
            enqueue(queue, cur); // вложить в очередь текущий узел
        }
    }
    free(queue);
}


int main(){
    int stime;
    long ltime;

    /* получение текущего календарного времени */
    ltime = time (NULL);
    stime = (unsigned int) ltime/2;
    srand(stime);
    
    const int m = 4;
    struct tree* tree = (struct tree*)malloc(sizeof(struct tree));
    tree->koren = NULL;
    tree->number_children = m;

    add(tree,5);
    add(tree,3);
    add(tree,4);
    add(tree,10);
    add(tree,8);
    add(tree,15);

    
    printf("DFS: ");
    dfs_print(tree->koren);
    printf("\n");
    printf("BFS: ");
    bfs_print(tree);
    printf("\n");
    

    return 0;
}
