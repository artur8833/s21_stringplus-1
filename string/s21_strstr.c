#include "../s21_string.h"

// Находит первое вхождение всей строки needle (не включая завеершающий нулвой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *temp = S21_NULL;
  s21_size_t haystack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);
  if (needle_len == 0) {
    temp = (char *)haystack;
  } else {
    while (*haystack != '\0' && haystack_len >= needle_len) {
      if (*haystack == *needle) {
        char *ha = (char *)haystack;
        char *ne = (char *)needle;
        while (*ha == *ne && *ne != '\0') {
          ha++;
          ne++;
        }
        if (*ne == '\0') {
          temp = (char *)haystack;
          break;
        }
      }
      haystack++;
      haystack_len--;
    }
  }
  return temp;
}
