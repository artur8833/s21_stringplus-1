#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  for (int i = 0; i < (int)s21_strlen(str1) + 1; i++) {
    for (int j = 0; j < (int)s21_strlen(str2) + 1; j++) {
      if (str1[i] == str2[j]) {
        return i;
      }
    }
  }
  return 0;
}