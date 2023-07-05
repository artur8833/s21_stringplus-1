#include "s21_string.h"
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.

char *s21_strchr(const char *str, int c) {
  void *ptr = (void *)str;
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    if (str[i] == c) {
      ptr = ptr + i;
      break;
    } else if (i == (int)s21_strlen(str) - 1) {
      ptr = NULL;
    }
  }
  return ptr;
}