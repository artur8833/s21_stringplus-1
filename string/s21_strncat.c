#include "../s21_string.h"
// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов. функция возвращает указатель на строку.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0, j = 0;
  while (dest[i] != '\0') {
    i++;
  }
  while (j < n) {
    dest[i++] = src[j++];
  }
  dest[i] = '\0';
  return dest;
}