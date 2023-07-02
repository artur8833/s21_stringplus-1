#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;
  for (int i = 0; i < (int)s21_strlen(str1) + 1; i++) {
    res = str1[i] - str2[i];
    printf("%c, %c %d\n", str1[i], str2[i], res);
    if (res != 0) {
      break;
    }
  }
  return res;
}