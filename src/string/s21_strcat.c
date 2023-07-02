#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int i = 0;
  int j = 0;
  while (dest[i] != '\0') {
    i++;
  }
  while (j < (int)s21_strlen(src)) {
    dest[i++] = src[j++];
  }
  return dest;
}