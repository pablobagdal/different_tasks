/* 
   
   ZADANI
   ------
  
   RUN LENGTH ENCODING (RLE) это очень простой принцип сжатия без потерь.
   Давайте объясним это на примере последовательностей символов, а позже поговорим о том, 
   как применить это в простой программе сжатия. Входным сигналом RLE является последовательность символов 
   (символ находится здесь как абстрактное понятие, не обязательно символ ASCII).
   Здесь мы преобразуем в сжатую форму с помощью следующего принципа:
   
   Если в строке есть n-кратный символ x, мы сжимаем его с помощью вспомогательной пары (x, n)

   Например, последовательность aaabaabcccccbccccd мы кодируем с помощью RLE последовательность
   (a,3)(b,1)(a,2)(b,1)(c,5)(b,1)(c,3)(d,1).

   Алгоритм сжатия и декомпрессии прост, и мы не будем его здесь объяснять.
   Его можно найти, например, на https://ru.wikipedia.org/wiki/Кодирование_длин_серий.

   Реализация:
   
   При сжатии мы будем считывать двоичный файл (не текстовый!!!). Мы рассматриваем один байт как один символ (и у нас есть 256 различных символов), 
   весь файл на самом деле представляет собой последовательность символов, которые мы используем для RLE.

   Пару (a, x), где a - символ, а x - количество его вхождения, мы сохраним двумя байтами в результирующий файл, 
   поместим символ a в первый байт, число x - 1 - во второй байт.
   ПОЭТОМУ МЫ ХРАНИМ ЭТУ ИНФОРМАЦИЮ В ДВОИЧНОМ ВИДЕ, А НЕ В ТЕКСТОВОМ!!!
   Мы можем хранить только пары, для которых x равно максимум 256.
   Поэтому мы модифицируем RLE таким образом, чтобы последовательность символа a, длина которой превышает 256, 
   кодировалась с помощью большего количества пар.
   Например, последовательность, где x равно 520, кодируется как (a, 256) (a, 256) (a, 1).
   
   ЗАДАЧА:

   Реализовывать функции

   void RLE_encode(char* in_path, char *out_path);
   void RLE_decode(char* in_path, char *out_path);

   которые кодируют / декодируют содержимое файла по пути in_path и сохраняют результат в файле out_path.

   Программу можно протестировать, сжав и распаковав файл и сравнив результат с исходным файлом.


  POPIS ZNAKU
  'r' otevreno pro cteni
  'w' otevreno pro zapis, existujici soubor je prepsan
  'a' otevreno pro zapis, pokud soubor existuje, zapisujeme
  na jeho konec
  't' otevreno v textovem rezimu
  'b' otevreno v binarnim rezimu

  PRIKLADY KOMBINACI
  "rt" cteni v textovem rezimu
  "wt" zapis v textovem rezimu
  "rb" cteni v binarnim rezimu
  "wb" zapis v binarnim rezimu
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fprintf_separated_to_binary_file(FILE* fd, char ch, size_t counter) {
    int celaia_chast = counter / 256;
    int drobnaia_chast = counter % 256;

    for (size_t i = 0; i < celaia_chast; i++)
    {
        fprintf(fd, "%c", ch);
        fprintf(fd, "%c", 256); 
    } 
    if(drobnaia_chast != 0) {
        fprintf(fd, "%c", ch);
        fprintf(fd, "%c", (int)counter);    
    }
}

void RLE_encode(char* in_path, char* out_path) {
    FILE* input_file = fopen(in_path, "rb");
    FILE* output_file = fopen(out_path, "wb");

    if (input_file == NULL || output_file == NULL) {
        printf("Error\n");
        exit(1);
    }
    
    size_t count;
    char* text = fgetln(input_file, &count);
    
    if(count == 0) {
        //input is empty
        fclose(input_file);
        fclose(output_file);
        return;
    }

    char* buffer_ptr = &text[0];
    int counter = 1;

    
    for (size_t i = 1; i < count; i++)
    {
        if(*buffer_ptr != text[i]) {
            fprintf_separated_to_binary_file(output_file, *buffer_ptr, counter);
            
            buffer_ptr = &text[i];
            
            counter = 1;
        } else {
            ++counter;
        }
    }
    fprintf_separated_to_binary_file(output_file, *buffer_ptr, counter);

    fclose(input_file);
    fclose(output_file);
}

void RLE_decode(char* in_path, char *out_path){
    FILE* input_file = fopen(in_path, "rb");
    FILE* output_file = fopen(out_path, "wb");

    if (input_file == NULL || output_file == NULL) {
        printf("Error\n");
        exit(1);
    }
     
    size_t count;
    char* text = fgetln(input_file, &count);
    
    if(count == 0) {
        //input is empty
        fclose(input_file);
        fclose(output_file);
        return;
    }

    // ++a a++

    for (size_t i = 0; i < count; i+=2)
    {
        size_t count = text[i+1];
        
        if((int)text[i+1] == 0) {
            count = 256;
        }

        for (size_t j = 0; j < count; j++)
        {
            fprintf(output_file, "%c", text[i]);
        }
    }
    
    fclose(input_file);
    fclose(output_file);
}

int main(){

    RLE_encode("input.txt", "output.txt");
    RLE_decode("output.txt", "input3.txt");


    return 0;
}


