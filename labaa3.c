#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stddef.h>

#define Dragon "Dragon flew away!"

int main()

{

  // сцена счетчиков

  int countb = 0, counta = 0;

  // начальная емкость буфера

  int flag = 0;
  
  // флаг для выхода

  int capacity = 256;

  // размер буфера и размер динамической строки

  int size = 0, dinamic_size = 0;

  // указатели на выделенную память

  char *str, *n_str;

  // счет с пяти

  int fives = 0;

  // выделенная память

  str = (char*)malloc(capacity);

  // если распределение было неудачным -  return

  if (str == NULL) return -1;



  char c;

  // читать символы с stdin

  do

  {
      // читать символы с stdin

      c = getchar();

    // если предложение слишком длинное,нужно перераспределить память

    if (size >= capacity - 2)

    {

      // удвоить емкость

      capacity = capacity * 2;

      // перераспределение памяти

      n_str = (char*)realloc(str, capacity);

      // если перераспределение было неуспешным 

      if (n_str == NULL)

      {

        // free previous allocation

        free(str);

        // return

        return -1;

      }

      str = n_str;

    }

    //если это перенос строки

    if(c == '\n')
    
    {
      //то перходим к следущему символу

      continue;

    }  

    // если это пустой символ в начале строки

    if ((c == ' ' || c == '\t') && size == 0)

    {

      // перейдите к следующему символу

      continue;

    }

    // сохранить символ в памяти

    str[dinamic_size+size] = c;

    // увеличить размер

    size++;

    // если это пять

    if (c == '5')

    {

      // увеличивать количество пяти

      fives = fives + 1;

    }

    else if (fives != 3)

    {

      // если это еще один символ, а число пятерок не равно пяти - установленным fives, равным нулю
      fives = 0;

    }

    // если это конец предложения

    if (c == '.' || c == '?' || c == ';')

    {

      // если суффикс содержит 555 - пропустите его
      if (fives != 3)

      {

        // добавить символ переноса строки в конец

        str[dinamic_size+size] = '\n';

        //увеличиваем длину динамической строки

        dinamic_size+=(size+1);             

        // увеличивать количество правильных возражений

        counta = counta + 1;

      }

      //обнуляем число пятёрок

      fives = 0;

      //обнуляем длину буфера
        
      size = 0;

      // увеличивать количество всех отступлений

      countb = countb + 1;

    }


    // проверка на Dragon flew away!

    if((c == '!')&&(size>=17))

    { 

        // цикл на 17 символов

        for(int i =0; i<17;i++)

        {

             // сравнение строчки с консольной строкой

            if(str[dinamic_size+i] != Dragon[i])

            {
                //ставим флаг в ноль и прерываем цикл

                flag = 0;   
        
                break;
                
            }
               
            else
            
            {
                
                // ставим флаг в еденицу
                
                flag = 1;   
            
            }

            } 

        }
  }while(flag!=1);

  //вывод строки
   printf("%s\n",str); 

  // написать статистику

  printf("Количество предложений до %i и количество предложений после %i\n", countb, counta);

  // свободная выделенная память

  free(str);



  return 0;



}

