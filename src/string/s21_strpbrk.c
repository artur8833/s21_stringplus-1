#include "../s21_string.h"
// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  void *ptr = S21_NULL;
  s21_size_t str2_len = s21_strlen(str2);
  s21_size_t j = 0;
  while (j < str2_len) {
    ptr = s21_strchr(str1, str2[j]);
    if (ptr) {
      break;
      j++;
    }
  }
  return ptr;
}
