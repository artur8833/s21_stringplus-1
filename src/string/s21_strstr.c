#include "../s21_string.h"

// Находит первое вхождение всей строки needle (не включая завеершающий нулвой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  void *temp = S21_NULL;
  s21_size_t haystack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);
  if (haystack_len < needle_len) {
    temp = S21_NULL;
  } else {
    s21_size_t i = 0;

    while (i < haystack_len - needle_len + 1){
      s21_size_t j = 1;
      char * ha = (void*)haystack + i;
      char * ne = (void*)needle;
      if(*ha == *ne){
        while(j < needle_len){
          if(*ha++ != *ne++) {
            i++;
            break;
          }
          j++;
        } 
      } else i++;
      if(j == needle_len) {
        temp = (void*)haystack + i;
        break;
      }
    }
  }
  return temp;
}
