#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<locale.h>
#include<string.h>

int getLenght(int *arr) {
    int lenght = 0;

    for(int i = 0; arr[i] != '\0' ; i++) {
        lenght++;
    }
    return lenght;
}

void printArray(int* arr, int length){
    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
// array - массив
int main() {
    int mass4[] = {4,3,5,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};
    int mass8[] = {4,3,5,32,12,12,12,12,4,3,5,32,12,12,12,12,4,3,5,32,12,12,12,12,4,3,5,32,12,12};
    
    //printArray(mass4, getLenght(mass4));

    int a = getLenght(mass4);

    printf("mass4 leng = %d", a);

    if(a == -1) {
        printf("5 is not found");
    } else {
        printf("index of 5 is %d", a);
    }



    return 0;
}