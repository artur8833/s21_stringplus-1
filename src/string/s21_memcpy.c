#include "s21_string.h"
// Копирует n символов из src в dest. области памяти не могут пересекаться
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {

  for (int i = 0; i < (int)n; i++) {
    ((char *)dest)[i] = ((char *)src)[i];
    if ((int)n == i + 1) {
      ((char *)dest)[i + 1] = '\0';
    }
  }

  return dest;
}