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

int hash_function(char* string){
    // let's say string is always not empty
    int hash = string[0]; // the hash will be: 00000000 00000000 00000000 [this byte with ASCII code]
    hash %= TABLE_SIZE; 
    return hash;
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

    return table;
}

int add_ct(char* data, chaining_table* table){
    if(contains_ct(data, table)) {
        // if it's already exists then we won't add it again
        return 0;
    }

    int hash= table->hash(data);

    if(table->table[hash] == NULL) {
        table->table[hash] = create_node(data);
        return 1;
    }

    node* node_ptr = table->table[hash];

    if(node_ptr->data == data) {
        // already exists
        return 0;
    }

    while(node_ptr->next != NULL) {
        node_ptr = node_ptr->next;

        if(node_ptr->data == data) {
            // already exists
            return 0;
        }
    }

    node_ptr->next = create_node(data);
    return 1;

    // int position = -1;

    // for (size_t i = 0; i < table->size; i++)
    // {
    //     if(table->table[i] == NULL) {
    //         position = i;
    //         break;
    //     }
    // }
    
    // if(position == -1) {
    //     // no place in table
    //     return 0;
    // }

    // int hash = table->hash(data);
    // table->table[i] = hash;

    // return 1;
}
int remove_ct(char* data, chaining_table* table){
    int position = -1;

    int hash = table->hash(data);

    for (size_t i = 0; i < table->size; i++)
    {
        if(table->table[i] == hash) {
            // need to free the memory
            delete[]table[i];

            return 1;
        }
    }
    
    return 0;
}
int contains_ct(char* data, chaining_table* table){
    // int position = -1;
    int index = table->hash(data);

    if(table->table[index] == NULL) {
        return 0;
    }

    node* node_ptr = table->table[index];

    while(node_ptr != NULL) {
        if(node_ptr->data == data) {
            return 1;
        }

        node_ptr = node_ptr->next;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    chaining_table* c_t = create_chaining_table(SIZE, hash_function);

    add_ct("hello", c_t);
    remove_ct("hello", c_t);
    contains_ct("hello", c_t);
    return 0;
}






