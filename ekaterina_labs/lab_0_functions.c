#include<stdio.h>
#include<stdlib.h>
#include<math.h> // mathematics
#include<locale.h>

int find_max_of_two_int(int number1,int number2) {
    int max;
    
    if(number1 > number2)
    {
        max = number1;    
    } else {
        max = number2;
    }

    return max;
}

int sum(int a, int b) {
    return a+b;
}
int difference(int a, int b) {
    return a-b;
}
int multiplication(int a, int b) {
    return a*b;
}

void showMenu(float a, float b) {

    printf("Ваши числа %f и %f\n", a, b);
    printf("Выберите пункт из меню:\n");
    printf("1. сумма чисел\n");
    printf("2. разница чисел\n");
    printf("3. произведение чисел\n");
    printf("4. изменить выбранные числа\n");
    printf("0. завершить программу\n");
}

int main()
{
    char *locale = setlocale(LC_ALL, "");

    float a,b;
    char userChoice;

    printf("Введите первое число: ");

    scanf("%f", &a);

    printf("\nВведите второе число: ");

    scanf("%f", &b);
    
    showMenu(a,b);

    scanf("%c", &userChoice);

    if(userChoice == '1') {
        printf("Сумма равна %f", sum(a,b))
    } else if(userChoice == '2') {

    } else if(userChoice == '2') {
    
    }
    // ....
    else if(userChoice == '0') {
        return 0;
    } else {
        printf("Такого пункта нет");
    }


    return 0;
}
