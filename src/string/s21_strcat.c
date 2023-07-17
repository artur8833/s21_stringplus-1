#include "../s21_string.h"
// функция добавляет строку str к строке dest перезаписывая символы \0 в конце
// строки и добавляя к строке символ окончания \0.
// строки не могут пересекаться а в строке dest должно хватать места для
// размещения объедененных строк.
char *s21_strcat(char *dest, const char *src) {
  s21_size_t src_len = s21_strlen(src);
  s21_size_t i = 0, j = 0;
  while (dest[i] != '\0') {
    i++;
  }
  while (j < src_len) {
    dest[i++] = src[j++];
  }
  return dest;
}
