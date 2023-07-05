#include "s21_string.h"
// Разбивает строку str на ряд токенов, разделенных delim.

char *s21_strtok(char *str, const char *delim) {
  char *str_tok = str;
  static char *ptr = NULL;
  if (str != NULL) {
    for(int i = 0; i < (int)strlen(str); i++){
      if((ptr = s21_strchr(delim[i], str)) != NULL){
        printf("%s", ptr);
      } 
    }
  }
  return str_tok;
}

