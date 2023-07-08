//Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
//указатель на строку с сообщением об ошибке. Нужно объявить макросы, содержащие
//массивы сообщений об ошибке для операционных систем mac и linux. Описания
//ошибок есть в оригинальной библиотеке. Проверка текущей ОС осуществляется с
//помощью директив.

#include "s21_strerror.h"
#include <string.h>
#include <stdio.h>

// char* s21_strerror(int errnum) {
//   char *err_list[] = s21_errors;
//   char buff[100] = "";
//   if (errnum >= 0 && errnum < s21_N_error) {
//     s21_strcpy(buff, err_list[errnum]);
//     printf("%s", err_list[errnum]); // s21_strcpy(buff, err_list[errnum]);
//   } else {
//     printf("%s%d", s21_unknown_error, errnum); // s21_sprintf(buff, "%s%d", err_list[errnum], errnum);
//   }

//   return buff;
// }

char* s21_strerror(int errnum) {
  static char buff[100] = "";
  if (errnum >= 0 && errnum < s21_N_error) {
    char *err_list[] = s21_errors;
    strcpy(buff, err_list[errnum]);
  } else {
    sprintf(buff, "%s%d", s21_unknown_error, errnum);
  }

  return buff;
}

int main() {

  printf("%s", strerror("a"));
  printf("%s", s21_strerror("a"));
  return 0;
}
