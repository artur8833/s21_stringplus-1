#include "../s21_string.h"
// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *str_tok = S21_NULL;
  char *tok = S21_NULL;
  if (str != S21_NULL) {
    str_tok = str;
  }
  if (str_tok) {
    str = str_tok;
    while (*str_tok && s21_strchr(delim, *str_tok)) {
      str_tok++;
      str++;
    }
    while (*str_tok && !s21_strchr(delim, *str_tok)) {
      str_tok++;
    }
    while (*str_tok && s21_strchr(delim, *str_tok)) {
      *str_tok = '\0';
      str_tok++;
      break;
    }
    if (*str)
      tok = str;
    else
      tok = S21_NULL;
  }

  return tok;
}
