#include "../s21_string.h"
// Функция вычисляет длину начального сегмента строки str1 состоящего только из
// символов строки str2
s21_size_t s21_strspn(const char *str1, const char *str2) {
  int temp = 0;
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  s21_size_t i = 0;
  while (i < str1_len) {
    if (temp != 1) {
      for (s21_size_t j = 0; j < str2_len; j++) {
        if (str1[i] == str2[j]) {
          temp = 0;
          break;
        } else
          temp = 1;
      }
      if (temp != 1)
        i++;
    } else
      break;
  }
  return i;
}