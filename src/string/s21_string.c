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

  if(str != NULL) {
  int k = 0;
  int i = 0;
  int j_tok = 0;
    for (int j = 0; j < (int)s21_strlen(str);) {
      while(k < (int)strlen(delim)){
        if(str[j] != delim[k]){ 
          k++;
        } else {
          str_tok_var[i][j] = '\0';
          i++;
          j_tok = 0;
          k = 0;
          break;
        }
        if(k == (int)strlen(delim) - 1){
          str_tok_var[i][j_tok++] = str[j];
        }
      }
    }
  }  
  return NULL;
}

