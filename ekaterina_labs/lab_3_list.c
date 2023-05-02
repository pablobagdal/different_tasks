#include<stdio.h>
#include<string.h>

// Поскольку вы еще не можете распределять память динамически, вы можете заранее создать 
//все используемые узлы в Main (используя массив, содержащий все используемые узлы). 
//Ни один узел не будет появляться несколько раз в списке / очереди / стеке (т.е. вам не нужно это обрабатывать).

// Создайте структуру для узла (односторонего) связанного списка 
//(содержащего  int data и ссылку на следующий элемент next) и тип node для этих структур (typedef).

typedef struct Node {
    int data;
    struct Node* next;
};

//Создайте структуру для односторонне связанного списка 
//(то есть структуру, содержащую начало списка - первый узел) и тип list для этих структур (typedef).

typedef struct List {
    struct Node* first;

};

int length(struct List seznam){ //определение длины списка
    struct Node* aktualni = seznam.first;
    int counter = 0;
    while(aktualni != NULL){
        counter ++;
        aktualni = aktualni->next;
    }
    return counter;
}

void print_list(struct List seznam){ // выписка элементов отделенных запятой
    struct Node* aktualni = seznam.first;
    while(aktualni != NULL){
        printf("%d", aktualni->data);
        if(aktualni->next != NULL){
            printf(", ");
        }
        aktualni = aktualni->next;
    }
    printf("\n");
}

//добавление узла в начале списка
void add_start(struct List *seznam, struct Node *uzel){ 
    uzel->next = seznam->first;
    seznam->first = uzel;
}
// добавление узла в конце списка
void add_end(struct List *seznam, struct Node *uzel){ // при передаче существующих элементов списка в качестве uzel могут нарушиться связи
    struct Node* aktualni = seznam->first;
    while(aktualni->next != NULL){
        aktualni = aktualni->next;
    }
    aktualni->next = uzel;
    uzel->next = NULL;
}
////// Проверка (отсюда писала сама) //////

// добавление узла в указанное местоположение в списке (или в конец, если это местоположение не отображается в списке)

void add_position(struct List *seznam, struct Node *uzel, int position){
    
    struct Node* aktualni = seznam->first;
    for (int i = 1; i < position - 1 && aktualni != NULL; i++) {
        aktualni = aktualni->next;
    }
    if (aktualni != NULL) {
        uzel->next = aktualni->next;
        aktualni->next = uzel;
    }
} // ?? не добавляет в конец, если местоположение не отображается в списке ??

// удаление узла в начале списка ( возвращает 0 если что-то удалилось и - 1 если нет)
int remove_start(struct List *seznam){
    
    struct Node* aktualni = seznam->first;
    
    if(aktualni == NULL || seznam->first == NULL){
        return -1;
    } else if(aktualni->next != NULL){
        aktualni->next = aktualni->next->next;
    }
    return 0; 
} // ?? удаляет изначально первый узел (2), другая функция добавляет первый узел (78) ??

// удаление узла в конце списка ( возвращает 0 - если что-то удалилось и - 1 - если нет)
int remove_end(struct List *seznam){
    
    struct Node* aktualni = seznam->first;
    struct Node* previous = NULL;
    if(aktualni == NULL || seznam->first == NULL){
        return -1;
    }
    while(aktualni->next != NULL){
        previous = aktualni;
        aktualni = aktualni->next;
    }
    previous->next = NULL;
    return 0;
} // ?? удаляет последний узел, который другая функция добовляет (число 100) ??

// поиск узла в списке ( возвращает позицию узла в списке или -1 если его там нет)
int search(struct List *seznam, struct Node *uzel){
    struct Node* aktualni = seznam->first;
    int counter = 0;
    while(aktualni != NULL){
        if(aktualni == uzel){
            return counter;
        }
        aktualni = aktualni->next;
        counter++;
    }
    return -1;
} // не уверенна, что правильно поняла, как должна работать функция 

// удаление определенного узла из списка (возвращает 0, если узел был удален и - 1 если нет)
int remove(struct List *seznam, struct Node *uzel){
    struct Node* aktualni = seznam->first;
    struct Node* previous = NULL;

    while(aktualni != NULL){
        if(aktualni == uzel){
            previous->next = aktualni->next;
            return 0;
        }
        previous = aktualni;
        aktualni = aktualni->next;
    }
    return -1;

} // ?? не могу сообразить ?? 

int main(){
    
    struct Node array[10]={ {2 , NULL}, {3 , NULL},  {4, NULL}, {5 , NULL}, {6 , NULL}, {7 , NULL}, {10 , NULL}, {12 , NULL}, {15, NULL}, {20, NULL}};

    struct Node start;
    start.data = 78;
    start.next = NULL;

    struct Node end;
    end.data = 100;
    end.next = NULL;

    struct Node position_add;
    position_add.data = 168;
    position_add.next = NULL;

    struct List list; //объявление списка
    list.first = &array[0];//определение свойства списка
    
    struct Node* current = list.first; //указатель обращается
    
    for(int i = 0; i < 9; i++){
       current->next = &array[i+1];
       current = current->next; 
    }

    add_start(&list, &start);
    add_end(&list, &end);

    remove_start(&list);
    remove_end(&list);
    
    add_position(&list, &position_add, 5);


    printf("\n");
    print_list(list);

    printf("\nlength = %d\n", length(list));
    printf("\nPosition node = %d\n\n", search(&list, &array[8]));
    return 0;
}
