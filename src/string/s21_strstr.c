#include "../s21_string.h"

// Находит первое вхождение всей строки needle (не включая завеершающий нулвой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  void *temp = S21_NULL;

  // int j = 0;
  if (s21_strlen(haystack) < s21_strlen(needle)) {
    temp = S21_NULL;
  } else {
    s21_size_t i = 0;
    while (i < s21_strlen(haystack)){
      s21_size_t j = 1;
      char * ha = (void*)haystack + i;
      char * ne = (void*)needle;
      if(*ha == *ne){
        while(j < s21_strlen(needle)){
          if(*ha++ != *ne++) {
            i++;
            break;
          }
          j++;
        } 
      } else i++;
      if(j == s21_strlen(needle)) {
        temp = (void*)haystack + i;
        break;
      }
      // for(s21_size_t j = 0; j < s21_strlen(needle); j++){
      //   i++;
      //   ne++;
      // }
    }
  }
    // j = 0;
    // while ((temp = s21_strchr(haystack, needle[j])) == S21_NULL) {
    //   j++;
    //   break;
    // }
    // printf("%c<-\t->%c%d\n", haystack[i], needle[j], j);
  //   for (s21_size_t z = 0; z < s21_strlen(needle); z++) {
  //     if (haystack[i + z] != needle[z]) {
  //       temp = S21_NULL;
  //       i++;
  //       break;
  //     } else if (z < s21_strlen(needle)) {
  //       temp = (void *)haystack + i;
  //     }
  //   }
  //   if (temp != S21_NULL)
  //     break;
  // }
    
  return temp;
}
