#include "s21_string.h"
// Функция копирует n байтов из области памяти src в область памяти dest.
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char temp[n];
  char *s = s21_memcpy(temp, src, n);
  for (int i = 0; i < (int)n; i++) {
    temp[i] = s[i];
  }

  for (int i = 0; i < (int)n; i++) {
    ((char *)dest)[i] = temp[i];
  }
  return dest;
}