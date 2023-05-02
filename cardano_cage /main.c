#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// #include<conio.h>
void printMatrix(int size, char matr[size][size]) {
   printf("\n");

   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         printf("%c", matr[i][j]);
      }
      printf("\n");
   }
}

int strlen(int size, char text[size]) { // string lenght
    int i = 0;
    while(text[i] != '\0') {
        i++;
    }
    return i;
}

void decodeCardano(int size, char text[size][size], int grid[size][size]) {
    // прямой обход решетки
   printf("\n0˚:\n");

   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[i][j] == 1)
            printf("%c", text[i][j]);
   
 
   // поворот решетки на 90 градусов по часовой стрелке
   printf("\n90˚:\n");
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[size-j-1][i] == 1)
            printf("%c", text[i][j]);
   
 
   // поворот решетки на 180 градусов по часовой стрелке
   printf("\n180˚:\n");
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[size-i-1][size-j-1] == 1)
            printf("%c", text[i][j]);
   
 
   // поворот решетки на 270 градусов по часовой стрелке
   printf("\n270˚:\n");
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[j][size-i-1] == 1)
            printf("%c", text[i][j]); 
}

void encodeCardano(int size, char *text, int grid[size][size], char encoded_text[size][size]){
   int text_index = 0;

   int text_length = strlen(sizeof(text), text);

   // заполняем случайными символами всю матрицу
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         {
            encoded_text[i][j] = (char)(48+rand()%80);// подобрать исходя из таблицы ASCII
            // printf("%c", encoded_text[i][j]);
         }
   
   // 0˚
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[i][j] == 1)
         {
            encoded_text[i][j] = text[text_index];

            text_index++;
            if(text_index == text_length){
               return;
            }
         }

   // поворот решетки на 90 градусов по часовой стрелке
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[size-j-1][i] == 1)
         {
            encoded_text[i][j] = text[text_index];

            text_index++;
            if(text_index == text_length){
               return;
            }
         }

   // поворот решетки на 180 градусов по часовой стрелке
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[size-i-1][size-j-1] == 1)
         {
            encoded_text[i][j] = text[text_index];

            text_index++;
            if(text_index == text_length){
               return;
            }
         }

   // поворот решетки на 270 градусов по часовой стрелке
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         if (grid[j][size-i-1] == 1)
         {
            encoded_text[i][j] = text[text_index];

            text_index++;
            if(text_index == text_length){
               return;
            }
         }
}

int main()
{ 
   const int SIZE = 6;

   char text1[SIZE*SIZE] = "hello_world!";

   char *buf[SIZE] = {"guhoeg",
                      "llxoeg",
                      "bnce.g",
                      "utp!wg",
                      "nqwmpg"}; // матрица с зашифрованным текстом

    char encoded_text1[SIZE][SIZE] ={
        {'1', '2', '3', '4', '5', '6'},
        {'7', '8', '9', 'a', 'b', 'c'},
        {'d', 'e', 'f', 'g', 'h', 'i'},
        {'g', 'k', 'l', 'm', 'n', 'o'},
        {'p', 'q', 'r', 's', 't', 'u'},
        {'v', 'w', 'x', 'y', 'z', 'A'}}; // решетка Кардано

   // SIZE-1-j | i
   int grid1[SIZE][SIZE] ={
                          {0, 0, 0, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0},
                          {1, 1, 1, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0},
                          {1, 1, 0, 0, 0, 1},
                          {0, 0, 0, 1, 0, 1}}; // решетка Кардано
   // размер обоих матриц должен быть одинаковым


   char encoded_text[SIZE][SIZE];//двумерный массив в который будут вноситься шифровка и который будет дешифрован

   encodeCardano(SIZE, "Hello_World!! You will pass the exam", grid1, encoded_text);

   // Вывод закодированного текста
   printMatrix(SIZE, encoded_text);
   
   decodeCardano(SIZE, encoded_text, grid1);

   printf("\nProgram end\n");

   system("pause");
   return 0;
}
