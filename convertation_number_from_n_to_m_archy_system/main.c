// Перевод числа из системы счисления с основанием A в систему счисления 
// с основанием B. A=5;  B=6.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// #include<conio.h>

int strlen(char *text) { // string lenght
    int i = 0;

    while(text[i] != '\0') {
        i++;
    }
    return i;
}

void string_reverse(char *text) {
    char tmp;

    int len = strlen(text);

    int cycle_iterations = len / 2;

    for (int i = 0; i < cycle_iterations; i++)
    {
        tmp = text[i];
        text[i] = text[len - 1 - i];
        text[len - 1 - i] = tmp;
    }
}

// int count_signs(int number) {return count;}
char *Scale = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int dig2int(char symbol) {
    int lenght = strlen(Scale);
    for (int i = 0; i < lenght; i++)
    {
        if(Scale[i] == symbol) {
            return i;
        }
    } 
}

void convert_number_system(char buf[20], char number[20], int from, int to) {
    int i,j,k, curr_number = 0;
    int origin_number_lenght = strlen(number);
    int result_number_lenght = 0;
    int rest; // остаток

    //char buf[100];
    // преобразовать number в число, с которым можно делать операции 
    i = 0;

    while(1) {
        curr_number = curr_number*from + dig2int(number[i]);

        i++;

        if(i == origin_number_lenght) {
            break;
        }
    }

    // переводим в нужную систему
    i = 0;
    while(1) {
        rest = curr_number % to;
        
        buf[i] = Scale[rest];
        i++;
        
        result_number_lenght++;
        
        curr_number = curr_number / to;
        
        if(curr_number == 0) {
            break;
        }
    }

    // char tmp;

    // int cycle_iterations = result_number_lenght / 2;

    // for (int i = 0; i < cycle_iterations; i++)
    // {
    //     tmp = buf[i];
    //     buf[i] = buf[result_number_lenght - 1 - i];
    //     buf[result_number_lenght - 1 - i] = tmp;
    // }
    printf("%s\n", buf);
    string_reverse(buf);
    printf("%s\n", buf);    

    // передать сформированную строку
    // return buf;
}

void main()
{

    char str[80];

    scanf("%s", str);


    // int A;
    // int B;

    // char numA[20];
    // char numB[20];

    // printf("\nВведите систему А\n");
    // scanf("%d",&A);
    // printf("\nВведите число в системе А(%d)\n", A);
    // scanf("%d",&numA);
    // printf("\nВведите систему B\n");
    // scanf("%d",&B);

    // numB = convert_number_system(numA, A, B);
    
    // convert_number_system(numB, "101230", 10, 20);
    // printf("\n\n%s\n", numB);

    // printf("\n%d-чное число %d равняется %d в %d-чной системе счисления.\n", A, numA, numB, B);
}
