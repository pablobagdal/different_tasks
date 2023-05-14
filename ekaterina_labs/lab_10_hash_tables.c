// 1. Реализуйте структуры и следующую функциональность для хэш-таблиц над строками с решением коллизией (Метод цепочек)

// Разработайте все так, чтобы вашу таблицу можно было использовать со следующим API:
// chaining_table* create_chaining_table(int size, int (*hash)(char*));
// int add_ct(char* data, chaining_table* table);
// int remove_ct(char* data, chaining_table* table);
// int contains_ct(char* data, chaining_table* table);

// Вторым параметром процедуры create_chaining_table является указатель на хэш-функцию.
// Последние три процедуры вернут 1 при успешном выполнении (выполнении требуемой операции) 
// и 0 в противном случае (не найдено, не добавлено, не удалено и т.д.). 
// Выберите хэш-функцию для строк самостоятельно в соответствии с лекциями.

//2. Реализуйте структуры и следующую функциональность для хэш-таблиц над строками с решением коллизией (Открытая адресация). 

// Разработайте все так, чтобы вашу таблицу можно было использовать со следующим API:
// oa_table* create_oa_table(int size, int (*hash)(char*), int (*probe)(int, int));
// int add_oat(char* data, oa_table* table);
// int remove_oat(char* data, oa_table* table);
// int contains_oat(char* data, oa_table* table);

// Вторым параметром процедуры create_oa_table является указатель на хэш-функцию и третий указатель для функции разведки.
// Последние три процедуры вернут 1 при успешном выполнении (выполнении требуемой операции)  
// и 0 в противном случае (не найдено, не добавлено, не удалено и т.д.). 
// Выберите хэш-функцию для строк самостоятельно в соответствии с лекциями.

// Напишите main с примерами использования реализаций. 
// Для открытой адресации покажите использование в таблицах с линейной и квадратичной функцией опроса.

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 256

#define SPECIAL_VALUE "SOMETEXT"

// Function to implement `strcpy()` function 
char* strcpy(char* destination, const char* source)
{
    // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }
 
    // take a pointer pointing to the beginning of the destination string
    char *ptr = destination;
 
    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // include the terminating null character
    *destination = '\0';
 
    // the destination is returned by standard `strcpy()`
    return ptr;
}

// Function to implement strcmp function
int strcmp(const char *X, const char *Y)
{
    while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }
 
        // move to the next pair of characters
        X++;
        Y++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

typedef struct node{
    char* data;
    struct node* next;
} node;

node* create_node(char* data) {
    node* new_node = malloc(sizeof(node));

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

typedef struct chaining_table chaining_table;

struct chaining_table{ 
    int size; // размер таблицы
    int (*hash)(char*); // хэш функция
    node** table;
};

int hash_function(char* str){
    // summarize ASCII of all chars and then mod Table size 
    int hash = 0;

    int length = sizeof(str);
    
    for (size_t i = 0; i < length; i++)
    {
        hash += str[i];
    }
    
    hash %= TABLE_SIZE;

    return hash;
}

int probing_function_linear(int hash, int step) {
    int step = hash + step;
    return step;
}
int probing_function_squared(int hash, int step_base) {
    int step = hash + step_base*step_base;
    return step;
}

chaining_table* create_chaining_table(int size, int(*hash)(char*)){
    
    chaining_table* table = malloc(sizeof(chaining_table));

    // memory overflow
    if(table == NULL){
        return NULL;
    }

    table->size = size;
    table->hash = hash;
    table->table = malloc(sizeof(node*)*size);// malloc mem to N pointers of node's
    
    for (size_t i = 0; i < size; i++)
    {
        table->table[i] = NULL;
    }
    
    return table;
}

int contains_ct(char* data, chaining_table* table){
    int index = table->hash(data);

    if(table->table[index] == NULL) {
        return 0;
    }
    
    node* node_ptr = table->table[index];

    while(node_ptr != NULL) {
        if(node_ptr->data == data) {
            return 1;
        }
        // if(strcmp(node_ptr->data, data)) {
        //     return 1;
        // }

        node_ptr = node_ptr->next;
    }

    return 0;
}
int add_ct(char* data, chaining_table* table){
    if(contains_ct(data, table)) {
        // if it's already exists then we won't add it again
        return 0;
    }

    int index = table->hash(data);

    if(table->table[index] == NULL) {
        table->table[index] = create_node(data);
        return 1;
    }

    node* node_ptr = table->table[index];

    while(node_ptr->next != NULL) {
        node_ptr = node_ptr->next;
    }

    node_ptr->next = create_node(data);
    return 1;
}
int remove_ct(char* data, chaining_table* table){
    if(!contains_ct(data, table)) {
        return 0;
    }

    int index = table->hash(data);

    node* prev_ptr = table->table[index];
    node* node_ptr = table->table[index];

    while(node_ptr->data != data) {
        prev_ptr = node_ptr;
        node_ptr = node_ptr->next;
    }

    prev_ptr->next = prev_ptr->next->next;

    // free memory using node_ptr
    free(node_ptr);
    // node_ptr = NULL;

    return 1;
}

typedef struct oa_table oa_table;

struct oa_table {
    int size; // размер таблицы
    int (*hash)(char*); // хэш функция
    int (*probe)(int,int); // хэш функция
    char** table;
};

oa_table* create_oa_table(int size, int (*hash)(char*), int (*probe)(int, int)){
    oa_table* table = malloc(sizeof(oa_table));

    // memory overflow
    if(table == NULL){
        return NULL;
    }

    table->size = size;
    table->hash = hash;
    table->probe = probe;
    table->table = malloc(sizeof(char*)*size);

    for (size_t i = 0; i < size; i++)
    {
        table->table[i] = NULL;
    }
    

    return table;
}

int contains_oat(char* data, oa_table* table){
    int index = table->hash(data);

    if(table->table[index] == NULL) {
        return 0;
    }

    while(index < table->size) {
        if(table->table[index] == NULL) {
            return 0;
        }
        
        if(data == table->table[index]) {
            return 1;
        }
        // if(strcmp(data, table->table[index])) {
        //     return 1;
        // }

        // if(table->table[index] == SPECIAL_VALUE) {
        //     return 1;
        // }
        index = table->probe(index, 0);
    }
    // riched end of the array
    return 0;
}

int add_oat(char* data, oa_table* table){
    if(contains_oat(data, table)) {
        // already exists
        return 0;
    }

    int index = table->hash(data);

    // char* ptr = table->table[index];

    while(index < table->size) {
        if(table->table[index] == NULL) { // what about SPECIAL_VALUE places? Shall we write in there?
            table->table[index] = data;
            // strcpy(table->table[index], data);
            return 1;
        }
        index = table->probe(index, table->size);
    }
    return 0;
}
int remove_oat(char* data, oa_table* table){
    if(!contains_oat(data, table)) {
        return 0;
    }

    int hash = table->hash(data);
    int step = 0;
    int index  = hash + step;

    while (table->table[index] != NULL && index < table->size)
    {
        if(table->table[index] == data) {
            table->table[index] = SPECIAL_VALUE;
            return 1;
        }
        // if(strcmp(table->table[index], data)) {
        //     strcpy(table->table[index], SPECIAL_VALUE);
        //     return 1;
        // }
        ++step;
        index = table->probe(hash,step);
    }
    
    // btw unreachable place
    return 0;
}

int main(int argc, char const *argv[])
{
    
    // chaining_table* c_t = create_chaining_table(TABLE_SIZE, hash_function);

    // add_ct("hello1", c_t);
    // add_ct("hello2", c_t);
    // add_ct("hello3", c_t);
    
    // remove_ct("hello2", c_t);

    // if(contains_ct("hello2", c_t)) {
    //     printf("contains\n");
    // } else {
    //     printf("doesn't contains\n");
    // }


    oa_table* a_t = create_oa_table(TABLE_SIZE, hash_function, probing_function_linear);
    // oa_table* a_t = create_oa_table(TABLE_SIZE, hash_function, probing_function_squared);

    add_oat("hello1", a_t);
    add_oat("hello2", a_t);
    add_oat("hello3", a_t);
    
    remove_oat("hello2", a_t);

    if(contains_oat("hello2", a_t)) {
        printf("contains\n");
    } else {
        printf("doesn't contains\n");
    }


    return 0;
}






