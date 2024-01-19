#include "../s21_string.h"
// выполняет поиск первого вхождения символа "с" (беззнаковый тип) в первых "n"
// байтах строки, на которую указывает аргумент str.
// Совпадение первого байта с "c" (представленным как беззнаковый символ)
// останавливает выполнение операции.

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ch = (const unsigned char *)str;
  void *res = S21_NULL;
  s21_size_t i = 0;
  while (i < n) {
    if (ch[i] == c) {
      res = (void *)(ch + i);
      break;
    }
    i++;
  }
  return res;
}
