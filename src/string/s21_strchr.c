#include "s21_string.h"
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    if (str[i] == c)
      return (void *)str + i;
  }
  return NULL;
}