#include "s21_string.h"
// Находит первый символ в строке str1, который соответствует любому символу, указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  void *ptr = (void *)str1;
  for (int i = 0; i < (int)s21_strlen(str1) + 1; i++) {
    for (int j = 0; j < (int)s21_strlen(str2) + 1; j++) {
      if (str1[i] == str2[j]) {
        return ptr + i;
      }
    }
  }
  return 0;
}