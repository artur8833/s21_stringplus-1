#include "../s21_string.h"
// Копирует n символов из src в dest. области памяти не могут пересекаться
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dest_ch = (char *)dest;
  const char *src_ch = (const char *)src;
  s21_size_t i = n;
  while (i > 0) {
    *dest_ch++ = *src_ch++;
    i--;
  }
  return dest;
}