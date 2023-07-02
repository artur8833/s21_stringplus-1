#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    if (str[i] == c)
      return (void *)str + i;
  }
  return NULL;
}