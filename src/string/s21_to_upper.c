#include "../s21_string.h"
// Возвращает копию строки (str), преобразованной в верхний регистр
void *s21_to_upper(const char *str) {
  char *str_copy = malloc(s21_strlen(str) + 1);  // +1 для нулевого символа
  void *result = S21_NULL;

  int i;
  for (i = 0; *str != '\0'; i++) {
    str_copy[i] = *str;
    str++;
  }
  str_copy[i] = '\0';

  for (i = 0; str_copy[i] != '\0'; i++) {
    if (str_copy[i] >= 'a' && str_copy[i] <= 'z') {
      str_copy[i] -= 32;
    }
  }

  result = (void *)str_copy;
  return result;
}
