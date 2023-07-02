#include "s21_string.h"
// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  for (int i = 0; i < (int)n; i++) {
    res = str1[i] - str2[i];
    printf("%c, %c %d\n", str1[i], str2[i], res);
    if (res != 0) {
      break;
    }
  }
  return res;
}