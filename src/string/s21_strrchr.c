#include "../s21_string.h"
// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  s21_size_t str_len = s21_strlen(str) + 1;
  void *ptr = (void *)str;
  for (s21_size_t i = 0; i < str_len; i++) {
    if (str[i] == c) {
      ptr = (void *)str + i;
    }
  }
  return ptr - 1;
}