#include <string.h>
#include <stdio.h>

typedef struct {
  char*  data;
  int len;
} string;


string from_cstring(char *cstring) {

  string ret = {0};
  ret.data = cstring;
  ret.len  = strlen(cstring);
  if (ret.len == 0) { ret.data = 0; }
  return ret;
}

int string_eq(string a, string b) {
  return (a.len == b.len) && (a.data == b.data || !memcmp(a.data, b.data, a.len)); 
}
  

//
//  Функция возвращает строковый префикс str до символа-разделителя(delimiter), 
//  который, однако, не принадлежит результату. До аргумента remainder записывается оставшаяся 
//  часть строки (остаток) без разделителя и типо того.
//     возвращаемое значение + delimiter + remainder  = str    
//  (символ + означает соединение цепочек).
//
//  - если первый символ str является разделителем, возвращается пустая строка
//  - если str не содержит разделителя, результатом будет целая цепочка
//  - внимание, оставшаяся часть может быть пустой
//
string get_prefix(string str, char delimiter, string * remainder) {
  
  int delimeter_index = -1; // -1 чтобы такого индекса точно не было

  int isFound = 0; // но в целом нам это и не грозит, т.к. этот флажок следит,
   // был ли найден разделитель

  for(int i = 0; i < str.len; i++){ // по всей строке пойдём по каждому символу
    if(str.data[i] == delimiter){ // но если найдём
      delimeter_index = i; // то запомним его
      isFound = 1; // и поставим флажок НАЙДЕНО!
      break; // и прервём цикл обязательно, чтобы не встретить и не записать по
       //ошибке уже следующий попавшийся разделитель (если вдруг найдётся)
    }
  }

  if(!isFound){ // если флаг=0, то значит, что не нашли. Тогда
    *remainder = (string){ 0, 0 }; // по адресу, который хранит remainder
    return (string){str.data, str.len}; // возвращаем набор данных
     // а именно: мы явно указали: воспринимай это как структура string
      // далее даём ему указатель на наш массив char*, и сколько подряд 
       // символов из него он будет считать частью себя. Можно сказать иначе
        // с каким количеством подряд идущих символов и с данной конкретной
         // позиции в массиве он будет себя ассоциировать
          // это также говорит о том, что printf("%s", remainder) нам ничего
           // хорошего не даст. Это выполнит вывод всего набора символов, 
            // начиная с указываемого remainder->data (т.е. нулевой для него)
             // и т.д. пока не встетит символ конца строки '\0'
              // А КАК НАДО: вывести ровно столько, какова величина rem->len
  }

  // длина остатка = вся строка за вычетом разделителя и всего, что шло до него
  int remainder_len = str.len - delimeter_index - 1;
  *remainder = (string){ str.data + delimeter_index + 1, remainder_len };

  return (string){str.data, delimeter_index};
}

void get_prefix_tests() {

  printf("testing get_prefix\n");
  string s = from_cstring("zaklady  programovani");
  string rem = { 0 };
  string prf = { 0 }; 
  string res_1 = { s.data, 7 };
  string rem_1 = { s.data + 8, 13 };

  string res_2 = { 0 };
  string rem_2 = { s.data + 9, 12 };

  string res_3 = { s.data + 9, 12 };
  string rem_3 = { 0 };
  

  printf("[0] ");
  prf = get_prefix(s, ' ', &rem);
  if ( string_eq(prf, res_1) && string_eq(rem, rem_1)) { printf ("OK\n"); }
  else { printf("fail\n"); }

  

  printf("[1] ");
  prf = get_prefix(rem, ' ', &rem);
  if ( string_eq(prf, res_2) && string_eq(rem, rem_2)) { printf ("OK\n"); }
  else { printf("fail\n"); }
  

  printf("[2] ");
  prf = get_prefix(rem, ' ', &rem);
  if ( string_eq(prf, res_3) && string_eq(rem, rem_3)) { printf ("OK\n"); }
  else { printf("fail\n"); }  
}

//
//  преобразует число, записанное в виде строки в long
// - predpokladame kodovani v desitkove soustave - кодирование в 10ой системе
// - если первый символ не равен нулю или пуст, он возвращает 0
// pokud prvni symbol neni nula, nebo je s prazdne, vraci 0
// - это число может быть отрицательное
// - конец строки, не содержащей цифр, опущен
//

long string_to_long(string s) {
  long result = 0;
  int start = 0; 
  int found_digit = 0;

  int negative = 0;
  char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};

  int count = 0;
  char buff[30];
  char *pointer = buff;  // чтобы двигаться по буферу

  if(s.len == 0){  // дали пустую строку
    return result;  // возвращаем ноль
  } else if(s.data[0] == '0'){  // началась с нуля
    return result;  // возвращаем ноль
  } else if(s.data[0] == '-'){  // началось с минуса
    negative = 1;  // ставим галочку, что оно отрицательное
    start = 1;  // и делаем сдвиг для будущего цикла, чтобы игнорировать этот минус
  }

  for(int i = start; i < s.len; i++){
    found_digit = 0; // пока что цифра не найдена
    for(int j = 0; j < 10; j++) { // пошли искать
      if(s.data[i] == digits[j]) { // если попался
        found_digit = 1; // ставим флажок, что попался
        break;  // и дальше идти смысла - нет
      }
    }
    if(found_digit == 1) {  // ну а если попался
      *pointer = s.data[i];  // по адресу указателя кладём этот символ-цифру
      pointer++; // сдвигаем указатель на 1 байт (как бы вправо)
      count++;  // и счётчик наших цифорок тоже увеличиваем
    }
  }
  for (int i = 0; i < count; i++)  // а теперь по этим цифрам пойдём
  {
    result = result + (buff[i] & 0x0F); // & двоичная операция И (как умножение ноликов и единиц)
    result = result * 10;  // в итоге закинули в рез. и умножили на 10
  }
  result /= 10; // но в результате цикла мы лишний раз умножили на 10 на последней
   // итерации, поэтому надо разделить на 10

  if(negative == 1) {  // а если отрицало
    result *= -1;  // отрицай
  }

  return result;
}

void string_to_long_tests() {

  printf("testing string_to_long\n");
  string t[4];
  t[0] = from_cstring("120");
  t[1] = from_cstring("-62");
  t[2] = from_cstring("13kdasodi");
  t[3] = from_cstring("");

  long values[4] = {120, -62, 13, 0};

  for(int i = 0; i<4; i += 1) {
    printf("[%i] ", i);
    if (values[i] == string_to_long(t[i])) { printf("OK\n"); }
    else { printf("fail\n"); }
  }
}

//
// s - это текст, содержащий целые числа, разделенные пробелами в каждой строке (на каждом ряду)
// они могут быть отрицательными!!!
// Функция возвращает число, которое получено следующим образом
// - числа в каждой строке складываются
// сумма нечетных строк из общего результата вычитается, у четных строк прибавляется
// - для пустого s результат равен 0
// Pr. "2 2\n2 2 2\n-2 3"
//     сумма строк 4, 6, 1
//     результат -4 +6 -1 = 1
//     
long compute_the_thing(string s) {
   // ну, погнали
  string rem = s;  // в остаток сразу кладём всю строку, чтобы работать именно с rem
  string line = {0};  // хранение строки
  string prf = {0}; // хранение "слова"(или числа, символа или др. единицы)

  long total_result = 0; 
  long line_result = 0;
  long number = 0;
  int line_number = 1;

  while(rem.len != 0) { // пока остаток не пустой
    line = get_prefix(rem, '\n', &rem); // откусываем от него в лайн

    while(line.len != 0) {  // пока лайн не пустой
      prf = get_prefix(line, ' ', &line);  // откусываем от него в преф

      if(prf.len != 0) {  // ЕСЛИ преф не пустой
        number = string_to_long(prf);  // преобразовываем в ЛОНГ и кидаем в намб
        line_result += number;  // увеличиваем сумму этой строки
      }
    }

    if(line_result != 0) {  // если сумма строки не нулевая(иначе в ней не было цифр)
      if(line_number % 2 == 1) {  // если нечётная строка
        line_result *= -1;  // отрицалово
      }

      total_result += line_result;  // кидаем в тотал
    }
    line_result = 0;  // обнуляем сумму строки для следующей итерации
    line_number++;  // увеличиваем номер строки для след.итерации
  }

  return (long)total_result;
}

void compute_the_thing_tests() {

  printf("testing compute_the_thing \n");
  string t[3];
  t[0] = from_cstring("2 2\n"
		      "2 2 2\n"
		      "-2 3\n");
  t[1] = from_cstring("");
  t[2] = from_cstring("-3 4\n\n\n12 5");
  
  int values[3] = { 1, 0, 16 };

  for(int i = 0; i<3; i += 1) {
    printf("[%i] ", i);
    if (values[i] == compute_the_thing(t[i])) { printf("OK\n"); }
    else { printf("fail\n"); }
  }
}


int main() {

  get_prefix_tests();
  printf("\n");
  string_to_long_tests();
  printf("\n");
  compute_the_thing_tests();  
}