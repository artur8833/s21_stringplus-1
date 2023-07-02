#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int i = 0;
  int j = 0;
  while (dest[i] != '\0') {
    i++;
  }
  while (j < (int)n) {
    dest[i++] = src[j++];
  }
  return dest;
}