#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  for (int i = 0; i < (int)s21_strlen(src) + 1; i++) {
    dest[i] = src[i];
  }
  return dest;
}
