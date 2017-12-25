#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define Dragon "Dragon flew away!"

int main(){
  int countb = 0, counta = 0;   // сцена счетчиков
  int flag = 0; // флаг для выхода
  int capacity = 256;   // начальная емкость буфера
  int size = 0, dinamic_size = 0;  // размер буфера и размер динамической строки
  char *str, *n_str;    // указатели на выделенную память
  int fives = 0;    // счет с пяти

  str = (char*)malloc(capacity);    // выделенная память
  if (str == NULL) return -1;   // если распределение было неудачным -  return

  char c;  

  do{   
        c = getchar();  // читать символы с stdin
        
        if ((dinamic_size+size) >= capacity - 2){  // если предложение слишком длинное,нужно перераспределить память  
            capacity = capacity * 2;  // удвоить емкость
            n_str = (char*)realloc(str, capacity);    // перераспределение памяти

            if (n_str == NULL){    // если перераспределение было неуспешным 
                free(str);  // free previous allocation
                return -1;  // return
            }

            str = n_str;
        }
        if(c == '\n') continue; //если это перенос строки, то перходим к следущему символу
        if ((c == ' ' || c == '\t') && size == 0)   continue;
        // если это пустой символ, табуляция в начале строки, то переходим к следующему символу 

        str[dinamic_size+size] = c;  // сохранить символ в памяти

        size++;    // увеличить размер 

        if (c == '5'){   // если это пять
            fives++; // увеличивать количество пятёрок
        }else if (fives != 3){  
            fives = 0;
            // если это еще один символ, а число пятерок не равно трём - установленным fives, равным нулю
        }        

        if (c == '.' || c == '?' || c == ';'){   // если это конец предложения
            // если суффикс содержит 555 - пропустите его
            if (fives != 3){
                str[dinamic_size+size] = '\n';   // добавить символ переноса строки в конец

                dinamic_size+=(size+1); //увеличиваем длину динамической строки
                counta = counta + 1;    // увеличивать количество правильных возражений
            }
            fives =0;
            countb = countb + 1; // увеличивать количество всех отступлений
            size = 0;   //обнуляем длину буфера
        }

        if((c == '!')&&(size>=17)){ // проверка на Dragon flew away!
            for(int i =0; i<17;i++){ // цикл на 17 символов
                if(str[dinamic_size+i] != Dragon[i]){ // сравнение строчки с консольной строкой
                    flag = 0;   //ставим флаг в ноль и прерываем цикл
                    break;
                }else{
                    flag = 1;   // ставим флаг в еденицу
                }
            }         
        }

  }while(flag!=1);  // проверка на флаг выхода
  
    printf("%s\n",str); //вывод строки
    printf("Количество предложений до %i и количество предложений после %i\n", countb, counta); // написать статистику

    free(str);  // высвобождение выделенной памяти
    return 0;
}
