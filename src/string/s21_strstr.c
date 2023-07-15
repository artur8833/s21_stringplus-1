#include "../s21_string.h"

// Находит первое вхождение всей строки needle (не включая завеершающий нулвой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  void *temp = S21_NULL;

  int j = 0;
  for (s21_size_t i = 0; i < s21_strlen(haystack); i++) {
    if (s21_strlen(haystack) < s21_strlen(needle)) {
      temp = S21_NULL;
    }
    j = 0;
    while ((temp = s21_strchr(haystack, needle[j])) == S21_NULL) {
      j++;
      break;
    }
    // printf("%c<-\t->%c%d\n", haystack[i], needle[j], j);
    for (s21_size_t z = 0; z < s21_strlen(needle); z++) {
      if (haystack[i + z] != needle[z]) {
        temp = S21_NULL;
        i++;
        break;
      } else if (z < (int)s21_strlen(needle)) {
        temp = (void *)haystack + i;
      }
    }
    if (temp != S21_NULL)
      break;
  }
  return temp;
}

// (temp = s21_strchr(haystack, *needle)) != S21_NULL; i++