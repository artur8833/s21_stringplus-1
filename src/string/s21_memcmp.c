#include "s21_string.h"
// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  char *x = (char *)str1, *y = (char *)str2;
  int res = 0;
  for (int i = 0; i < (int)n; i++) {
    res = *x++ - *y++;
    if (res != 0) {
      break;
    }
  }
  return res;
}