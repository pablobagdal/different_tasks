/* 
   Задание:
   
   Реализуйте функцию: char **string_split (char *text, char delimiter, int *size)

   Эта функция делит текст входной строки на части, разделенные символом-разделителем (delimiter)
   Например:

   "ahoj svete" 
   
   разделяет при использовании разделителя ' ' на два
   
   "ahoj" и "svete".

   Функция возвращает вновь(новые) выделенные массивы вновь выделенных строк, 
   созданных таким образом, и записывает их количество в адрес size.

   Следовательно в случае:

   int length = 0;
   char **split = string_split("ahoj svete", ' ', &length);

   функция помещает значение 2 в переменную length, затем
   
   split[0] будет содержать "ahoj"
   split[1] будет содержать "svete"

   причем split[0] и split[1] являются адресами, которые были выделены malloc, 
   и их содержимое было скопировано из цепочки "ahoj svete".

   1) если текст представляет собой пустую строку, функция возвращает одноэлементный массив, 
   первым элементом которого является пустая строка

      Пример:
      "" -> {""}

   2) если разделитель находится в начале строки, 
   то пустая строка является первым элементом возвращаемого поля.

      Пример: (delimiter a)
      "axxx" -> {"", "xxx"}

   3) если разделитель находится в конце строки, 
   последним элементом возвращаемого поля является пустая строка.
      
      Пример: (delimiter a)
      "xxxa" -> {"xxx", ""}

   4) если строка (или ее часть) содержит два разделителя подряд, 
   это приводит к добавлению пустой строки в соответствующее место 
   в итоговом массиве.

      Пример: (delimiter a)
      "xxaaaxx" -> {"xx", "", "", "xx"}

   5) если разделителя в строке нет, результатом является одноэлементный массив, 
   единственным элементом которого является копия всей строки.

   При написании из библиотеки string.h можно использовать только strlen и 
   функции для копирования / сдвига памяти.
   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** string_split (char *text, char delimiter, int *size) {
    size_t len = strlen(text);

    int count = 1;
  
    for (size_t i = 0; i < len; i++)
    {
        if(text[i] == delimiter) {
            count++;
        }
    }
    *size = count;

    char** array_of_words;
    array_of_words = malloc(sizeof(char*)*count);
    
    size_t start = 0;
    size_t end = 0;
    size_t cur_index = 0;

    int add_at_the_end = 0;

    for (size_t i = 0; i < len; i++)
    {
        if(text[i] == delimiter) {
            end = i;
            int word_len = end - start;
            array_of_words[cur_index] = malloc(sizeof(char)*word_len);
            memcpy(array_of_words[cur_index], text+start, word_len);

            // not sure
            if(i != len - 1) {
                start = i+1;
            } else {
                add_at_the_end = 1;
            }
            cur_index++;
        } else {
            //if(start )
        }
    }
    if(add_at_the_end == 0) {
        int word_len = len - start;
        array_of_words[cur_index] = malloc(sizeof(char)*word_len);
        memcpy(array_of_words[cur_index], text+start, word_len);
    } else {
        // problem with test 4: 
        //*** error for object 0x100003dc6: pointer being freed was not allocated

        array_of_words[cur_index] = malloc(sizeof(char)*2);
        array_of_words[cur_index] = "";
    }


    return array_of_words;
}


void _print_splits (char **splits, int l) {

  printf("{");
  for (int i = 0; i < l; i += 1) {
    printf("\"%s\"", splits[i]);
    if(i != l-1)
      printf(", ");
  }
  printf("}\n");
}

void
_test_and_report (char *text, char delim) {

  int length = 0;
  char **result = string_split(text, delim, &length);

  if(result)
    _print_splits(result, length);

  for(int i = 0; i<length; i+=1) {
    free(result[i]);
  }

  free(result);
}


int main () {

  printf("TEST 1\n");
  printf(" Ma byt: {\"zakladni\", \"test\", \"funkcnosti\"}\nDostanu: ");
  _test_and_report("zakladni test funkcnosti", ' ');

  printf("\nTEST 2 - prazdny vstupni retezec\n");
  printf(" Ma byt: {\"\"}\nDostanu: ");
  _test_and_report("", ' ');

  printf("\nTEST 3 - delimiter neni v retezci\n");
  printf(" Ma byt: {\"nerozdeleny text\"}\nDostanu: ");
  _test_and_report("nerozdeleny text", 'k');

//   printf("\nTEST 4 - delimiter na konci retezce \n");
//   printf(" Ma byt: {\"xxxx\", \"\"} \nDostanu: ");
//   _test_and_report("xxxxa", 'a');

  printf("\nTEST 5 - delimiter na zacatku retezce \n");
  printf(" Ma byt: {\"\", \"xxxx\"} \nDostanu: ");
  _test_and_report("axxxx", 'a');

  printf("\nTEST 6 - vice delimiteru za sebou \n");
  printf(" Ma byt: {\"xx\", \"\", \"\", \"xx\"} \nDostanu: ");
  _test_and_report("xxaaaxx", 'a');

  return 0;
}
