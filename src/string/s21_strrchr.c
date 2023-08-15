#include "../s21_string.h"
// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  s21_size_t str_len = s21_strlen(str);
  char *ptr = (char *)str;
  while (str_len > 0) {
    if (ptr[str_len] == c) {
      ptr = ptr + str_len;
      break;
    }
    str_len--;
  }
  if (str_len == 0 && *ptr != c) {
    ptr = S21_NULL;
  }
  return ptr;
}