#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
};
typedef struct node node;

struct list
{
    node *begin;
};
typedef struct list list;

int length(list seznam)
{
    int length = 0;
    node *current = seznam.begin;

    while (current != NULL)
    {
        ++length;
        current = current->next;
    }

    return length;
}

void print_list(list seznam)
{
    node *current = seznam.begin;

    if (current != NULL)
    {
        printf("%d", current->value);

        while (current->next != NULL)
        {
            current = current->next;
            printf(", %d", current->value);
        }

        printf("\n");
    }
}

void add_start(list *seznam, int data)
{
    node *uzel = (node *)malloc(sizeof(node));
    uzel->value = data;
    uzel->next = seznam->begin;
    seznam->begin = uzel;
}

void add_end(list *seznam, int data)
{
    node *current = seznam->begin;
    node *uzel = (node *)malloc(sizeof(node));

    uzel->value = data;
    uzel->next = NULL;

    if (current == NULL)
    {
        seznam->begin = uzel;
    }
    else
    {
        while (current->next != NULL)
            current = current->next;

        current->next = uzel;
    }
}

void add_position(list *seznam, int data, int position)
{
    node *current_node = seznam->begin;
    int current_position = 1;
    node *uzel;

    if ((current_node == NULL) || (position == 0))
    {
        add_start(seznam, data);
    }
    else
    {
        while ((current_node->next != NULL) && (current_position != position))
        {
            current_node = current_node->next;
            ++current_position;
        }

        uzel = (node *)malloc(sizeof(node));
        uzel->value = data;
        uzel->next = current_node->next;
        current_node->next = uzel;
    }
}

int remove_start(list *seznam)
{
    node *previous_begin;

    if (seznam->begin == NULL)
    {
        return -1;
    }
    else
    {
        previous_begin = seznam->begin;
        seznam->begin = previous_begin->next;
        free(previous_begin);

        return 0;
    }
}

int remove_end(list *seznam)
{
    node *current = seznam->begin;

    if (current == NULL)
    {
        return -1;
    }
    else if (current->next == NULL)
    {
        free(current);
        seznam->begin = NULL;
        return 0;
    }
    else
    {
        while (current->next->next != NULL)
            current = current->next;

        free(current->next);
        current->next = NULL;
        return 0;
    }
}

int search(list *seznam, int data)
{
    node *current = seznam->begin;
    int position = 0;

    while ((current != NULL) && (current->value != data))
    {
        current = current->next;
        ++position;
    }

    if (current == NULL)
        return -1;
    else
        return position;
}

int remove_node(list *seznam, int data)         
{
    node *current = seznam->begin;
    node *tmp;

    if ((current != NULL) && (current->value == data))
    {
        return remove_start(seznam);
    }
    else
    {
        while ((current != NULL) && (current->next->value != data))
            current = current->next;

        if (current == NULL)
        {
            return -1;
        }
        else
        {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp);

            return 0;
        }
    }
}

struct tree_node
{
    int value;
    struct tree_node *left_child;
    struct tree_node *right_child;
};
typedef struct tree_node tree_node;

struct tree
{
    struct tree_node *root;
};
typedef struct tree tree;

void add(tree *t, int data)
{
    tree_node *node = t->root;

    if (node == NULL)
    {
        t->root =(tree_node *)malloc(sizeof(tree_node));
        t->root->value = data;
        t->root->left_child = NULL;
        t->root->right_child = NULL;
    }
    else
    {
        for (;;)
            if (data < node->value)
                if (node->left_child == NULL)
                {
                    node->left_child = (tree_node *)malloc(sizeof(tree_node));
                    node->left_child->value = data;
                    node->left_child->left_child = NULL;
                    node->left_child->right_child = NULL;
                    return;
                }
                else
                {
                    node = node->left_child;
                }
            else if (node->right_child == NULL)
            {
                node->right_child = (tree_node *)malloc(sizeof(tree_node));
                node->right_child->value = data;
                node->right_child->left_child = NULL;
                node->right_child->right_child = NULL;
                return;
            }
            else
            {
                node = node->right_child;
            }
    }
}

void print_in_order(tree t)
{
    struct frame
    {
        tree_node *node;
        unsigned char was_left_child_printed;
        struct frame *next;
    };

    struct frame *stack;
    struct frame *tmp;

    if (t.root != NULL)
    {
        stack = (struct frame *)malloc(sizeof(struct frame));
        stack->node = t.root;
        stack->was_left_child_printed = 0;
        stack->next = NULL;

        while (stack != NULL)
            if (stack->was_left_child_printed == 0)
            {
                stack->was_left_child_printed = 1;

                if (stack->node->left_child != NULL)
                {
                    tmp = (struct frame *)malloc(sizeof(struct frame));
                    tmp->node = stack->node->left_child;
                    tmp->was_left_child_printed = 0;
                    tmp->next = stack;
                    stack = tmp;
                }
            }
            else
            {
                printf("%d ", stack->node->value);

                if (stack->node->right_child != NULL)
                {
                    stack->node = stack->node->right_child;
                    stack->was_left_child_printed = 0;
                }
                else
                {
                    tmp = stack->next;
                    free(stack);
                    stack = tmp;
                }
            }

        printf("\n");
    }
}

int depth(tree t)
{
    struct frame
    {
        tree_node *node;
        unsigned char was_left_child_printed;
        struct frame *next;
    };

    struct frame *stack;
    struct frame *tmp;

    int max_depth = 0;
    int current_depth = 0;

    if (t.root != NULL)
    {
        stack = (struct frame *)malloc(sizeof(struct frame));
        stack->node = t.root;
        stack->was_left_child_printed = 0;
        stack->next = NULL;
        ++current_depth;

        while (stack != NULL)
        {
            if (stack->was_left_child_printed == 0)
            {
                stack->was_left_child_printed = 1;

                if (stack->node->left_child != NULL)
                {
                    tmp = (struct frame *)malloc(sizeof(struct frame));
                    tmp->node = stack->node->left_child;
                    tmp->was_left_child_printed = 0;
                    tmp->next = stack;
                    stack = tmp;
                    ++current_depth;
                }
            }
            else if (stack->was_left_child_printed == 1)
            {
                stack->was_left_child_printed = 2;

                if (stack->node->right_child != NULL)
                {
                    tmp = (struct frame *)malloc(sizeof(struct frame));
                    tmp->node = stack->node->right_child;
                    tmp->was_left_child_printed = 0;
                    tmp->next = stack;
                    stack = tmp;
                    ++current_depth;
                }
            }
            else
            {
                if (current_depth > max_depth)
                    max_depth = current_depth;
                --current_depth;

                tmp = stack->next;
                free(stack);
                stack = tmp;
            }
        }
    }

    return max_depth;
}

int tree_max(tree_node *root)
{
    while (root->right_child != NULL)
        root = root->right_child;
    return root->value;
}

int tree_min(tree_node *root)
{
    while (root->left_child != NULL)
        root = root->left_child;
    return root->value;
}

int tree_remove(tree *t, int data)
{
    tree_node **node = &t->root;
    tree_node *tmp, *tmp2;

    while ((*node != NULL) && ((*node)->value != data))
        if (data < (*node)->value)
            node = &(*node)->left_child;
        else
            node = &(*node)->right_child;
    
    if ((*node) == NULL)
    {
        return 0;
    }
    else if ((*node)->left_child == NULL)
    {
        tmp = (*node)->right_child;
        free(*node);
        *node = tmp;
        return 1;
    }
    else if ((*node)->right_child == NULL)
    {
        tmp = (*node)->left_child;
        free(*node);
        *node = tmp;
        return 1;
    }
    else
    {
        tmp = (*node)->left_child;
        tmp2 = (*node)->right_child;
        free(*node);
        *node = tmp;
        while (*node != NULL)
            node = &(*node)->right_child;
        *node = tmp2;
        return 1;
    }
}

void print_bft(tree *t)
{
    tree_node **mas;
    tree_node **childs;
    int mas_n = 1;
    int childs_n;
    int i, j;

    if (t->root != NULL)
    {
        mas = (tree_node **)malloc(sizeof(tree_node *));
        *mas = t->root;

        while (mas_n != 0)
        {
            childs = (tree_node **)malloc(mas_n * 2 * sizeof(tree_node *));
            childs_n = 0;

            for (i = 0; i < mas_n; i++)
            {
                printf("%d ", mas[i]->value);
                if (mas[i]->left_child != NULL)
                    childs[childs_n++] = mas[i]->left_child;
                if (mas[i]->right_child != NULL)
                    childs[childs_n++] = mas[i]->right_child;
            }

            free(mas);
            mas = childs;
            mas_n = childs_n;
        }

        free(mas);
        printf("\n");
    }
}

int main()
{
    tree t;
    t.root = NULL;

    add(&t, 78);
    add(&t, 85);
    add(&t, 12);
    add(&t, 60);
    add(&t, 71);
    add(&t, 0);
    add(&t, 92);
    add(&t, -3);
    add(&t, 80);
    add(&t, -5);
    add(&t, 5);

    print_bft(&t);
}