#include <stdio.h>
#include <stdlib.h>

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

typedef struct node{
    char* data;
    struct node* next;
}node;

typedef struct chaining_table{ 
    int size; // размер таблицы
    int (*hash)(char*); // хэш функция
    struct node** table;
}chaining_table;

int hash_function(char* string){
    
}

chaining_table* create_chaining_table(int size, int(*hash)(char*)){
    chaining_table* table = malloc(sizeof(chaining_table));
    if(table == NULL){
        return NULL;
    }
    table->size;
    table->hash;
}









