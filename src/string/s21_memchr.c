#include "s21_string.h"
// выполняет поиск первого вхождения символа "с" (беззнаковый тип) в первых "n"
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *ch = (char *)str;
  for (int i = 0; i < (int)n + 1; i++) {
    if (*ch == c)
      return ch;
    ch = (char *)str++;
  }
  return NULL;
}