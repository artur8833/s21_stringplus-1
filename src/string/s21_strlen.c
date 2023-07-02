#include "s21_string.h"

s21_size_t s21_strlen(const char *s) {
  int n = 0;
  while (s[n] != '\0') {
    n++;
  }
  return n;
}