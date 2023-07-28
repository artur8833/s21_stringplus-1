#include "../s21_string.h"
// Разбивает строку str на ряд токенов, разделенных delim.

char *s21_strtok(char *str, const char *delim) {
  static char *str_tok;
  char *tok = S21_NULL;
  if (str != S21_NULL) {
    str_tok = str;
    while (s21_strchr(delim, *str_tok)) {
      *str_tok = '\0';
      str_tok++;
    }
  }
  if(str_tok != S21_NULL){
    str = str_tok;
    while(!s21_strchr(delim, *str_tok)){
      str_tok++;
    }
    while(s21_strchr(delim, *str_tok)){
      *str_tok = '\0';
      str_tok++;
    }
  tok = str;
  }
  return tok;
}
