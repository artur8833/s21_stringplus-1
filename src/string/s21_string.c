#include "s21_string.h"

// void s21_memchr(const void *, int, size_t);
// size_t s21_strlen(const char *);

int main() {
  char str1[] = "Hello, World! How are you?";
  const char str2[] = " ,!?";

  char str3[] = "Hello, World! How are you?";
  const char str4[] = " ,!?";

  char *ptr1 = strtok(str1, str2);
  char *ptr2 = s21_strtok(str3, str4);
  strerror(0);
  while (ptr1 != NULL) {
    printf("    strcat:%s\n", ptr1);
    printf("s21_strcat:%s\n", ptr2);
    ptr1 = strtok(NULL, str2);
    ptr2 = s21_strtok(NULL, str4);
  }
  return 0;
}

// char *s21_strerror (int errnum){

// }

char *s21_strtok(char *str, const char *delim) {
  char *str_tok = str;
  static char *ptr = NULL;
  int k = 0;
  if (str != NULL) {
    for (int i = 0; i < (int)s21_strlen(str_tok) && k == 0; i++) {
      for (int j = 0; j < (int)s21_strlen(delim); j++) {
        if (str_tok[i] == delim[j]) {
          ptr = str_tok + i + 1;
          str_tok[i] = '\0';
          k = 1;
          break;
        }
      }
    }
  } else if (ptr != NULL) {
    str_tok = ptr;
    k = 0;
    for (int i = 0; i < (int)s21_strlen(ptr) && k == 0; i++) {
      for (int j = 0; j < (int)s21_strlen(delim); j++) {
        if (ptr[i] == delim[j]) {
          if (i == 0) {
            ptr = ptr + 1;
            str_tok = str_tok + 1;
          } else {
            ptr = ptr + i + 1;
            str_tok[i] = '\0';
            k = 1;
            break;
          }
        }
      }
    }
  }
  return str_tok;
}
