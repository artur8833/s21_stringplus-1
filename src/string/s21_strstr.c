#include "s21_string.h"
// Находит первое вхождение всей строки needle (не включая завершающий нулевой символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  void *temp = 0;
  int flag = 0;
  if (s21_strlen(haystack) < s21_strlen(needle)) {
    return NULL;
  }
  for (int i = 0; i < (int)s21_strlen(haystack); i++) {
    if (haystack[i] == *needle) {
      temp = (void *)haystack + i;
      for (int j = 0; j < (int)s21_strlen(needle); j++) {
        if (haystack[i + j] == needle[j]) {
          flag = 1;
        } else
          flag = 0, (void *)haystack;
      }
      if (flag)
        return temp;
    }
  }
  return temp;
}