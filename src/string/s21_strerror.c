//Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
//указатель на строку с сообщением об ошибке. Нужно объявить макросы, содержащие
//массивы сообщений об ошибке для операционных систем mac и linux. Описания
//ошибок есть в оригинальной библиотеке. Проверка текущей ОС осуществляется с
//помощью директив.

#include "s21_strerror.h"
#include "s21_string.h"
#include "s21_sprintf.h"

#include <string.h>
#include <stdio.h>

char* s21_strerror(int errnum) {
 // char *err_list[] = s21_errors;
  static char buff[100] = "";
  if (errnum >= 0 && errnum < s21_N_error) {
    char *err_list[] = s21_errors;
    s21_strcpy(buff, err_list[errnum]);
  } else {
    s21_sprintf(buff, "%s%d", s21_unknown_error, s21_N_error);
  }

  return buff;
}
