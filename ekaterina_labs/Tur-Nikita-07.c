#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int key;
    unsigned char height;
    struct node* left;
    struct node* right;
};

unsigned char height(struct node* p)
{
    return p ? p->height : 0;
}

int bfactor(struct node* p)
{
    return height(p->right) - height(p->left);
}

void fixheight(struct node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

struct node* rotateright(struct node* p)
{
    struct node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

struct node* rotateleft(struct node* q)
{
    struct node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

struct node* balance(struct node* p)
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

struct node* insert(struct node* p, int k)
{
    if (!p)
    {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        new_node->key = k;
        new_node->height = 1;
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void print_bfs(struct node* t)
{
    if (t == NULL)
        return;

    struct node** queue = (struct node**)malloc(sizeof(struct node*) * 100);
    int front = 0, rear = 0;
    queue[rear++] = t;

    while (front < rear)
    {
        int count = rear - front;
        while (count--)
        {
            struct node* node = queue[front++];
            printf("%d ", node->key);
            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
        printf("\n");
    }
    free(queue);
}

void deleteHelper(struct node* ptr)
{
    if (ptr != NULL)
    {
        deleteHelper(ptr->left);
        deleteHelper(ptr->right);
        free(ptr);
    }
}

int main()
{
    srand(time(0));
    struct node* t = NULL;
    int n = 20;
    while (n--)
        t = insert(t, rand() % 19 - 9);

    print_bfs(t);
    deleteHelper(t);

    return 0;
}
