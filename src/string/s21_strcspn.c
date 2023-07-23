#include "../s21_string.h"
// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t str1_len = s21_strlen(str1) + 1;
  s21_size_t str2_len = s21_strlen(str2) + 1;
  int count = 0;
  for (s21_size_t i = 0; i < str1_len && count == 0; i++) {
    for (s21_size_t j = 0; j < str2_len; j++) {
      if (str1[i] == str2[j]) {
        count = i;
        break;
      }
    }
  }
  return count;
}