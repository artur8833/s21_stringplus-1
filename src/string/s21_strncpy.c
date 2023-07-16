#include "../s21_string.h"
// Копирует до n символов из строки, на которую указывает src, в dest.
// не заполняется массив 0 если выделено больше памяти
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  return dest;
}