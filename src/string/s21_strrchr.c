#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  void *ptr = (void *)str;
  for (int i = 0; i < (int)s21_strlen(str) + 1; i++) {
    if (str[i] == c) {
      ptr = (void *)str + i;
    }
  }
  return ptr - 1;
}