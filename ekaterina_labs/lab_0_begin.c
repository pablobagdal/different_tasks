#include<stdlib.h> //
#include<stdio.h>  // standart input / output   
// #include<setlocale.h>

// setlocale( LC_ALL, "ru-RU" );

int func();

char main() {
    // это главная функция
    printf("Hello world!\n"); // \n - экранированный символ перехода на новую строку
    //func();
    int a = 4; //
    int b = a*10; 

    char a1 = '4';
    char b1 = a1*20;

    // ' ' - одиночные - для хранения одного символа
    // " " - двойный - для хранения набора символов
    printf("Variable b1 equal to %c", b1); 

    printf("Variable b equal to %d", b); 

    char S_ymbol12 = 'g'; // - - - -  - - - - 

    // int, char, void - типы данных 
    // int - integer - целочисленный
    // unsigned int - беззнаковый целочисленный
    // char - character - символ
    // float - плавающий 1.34
    // bool - boolean - бинарный - 0 или 1 - true или false
    // double - удвоенный

    // условный оператор

    if(/*условие*/) {
        // код программы, если условие истинно
    } 

    if(/*я проснулась в 6 утра*/ /*и / или */ /*условие 2*/) {
        // код программы, если условие истинно
    } else {
        // альтернативный код программы
    }
    // и - && - двойной амперсанд
    // или || - две палочки
    // не - ! - восклицательный знак



    // цикл




    return '0';
}


int func() {
    printf("goodbye");

    //return 0;
}



