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
  if(str != NULL) str_tok_var = (void *)str;
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    for (int j = 0; j < (int)s21_strlen(delim); j++) {
      if (str[i] == delim[j]) {
        return str_tok_var;
        str[j] = '\0';
        return str;
      }
    }
  }
  else

  return NULL;
}
