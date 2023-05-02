#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>

using namespace std;

void decode(){

}
void printMatrix() {

}

int main()
{
    const int SIZE = 6;

      char buf[SIZE][SIZE] = { "gfhfg",
                        "asdfg",
                        "asdfg",
                        "asddf",
                        "asdfg",
                        "asdeq"};

    // char *buf[SIZE] = {"guhoeg",
    //                   "llaoeg",
    //                   "aace.g",
    //                   "utp!wg",
    //                   "nqwmpg"}; // матрица с зашифрованным текстом
    
    int grid1[SIZE][SIZE] ={{0, 0, 0, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0},
                          {1, 1, 1, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0},
                          {1, 1, 0, 0, 0, 1},
                          {0, 0, 0, 1, 0, 1}};


    decode(buf, grid1);
    printMatrix();

    return 0;
}