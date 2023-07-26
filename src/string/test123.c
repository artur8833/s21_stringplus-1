#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "s21_string.h"


int main() {
  char s1[] = "kek_mem";
  char s2[] = "kek_mem";
  char s3[] = "kek_mem";
  char s4[] = "new_string";
  s21_size_t n = strlen(s4);
  char *ptr1 = memcpy(s1, s4, n);
  char *ptr2 = s21_memcpy(s2, s4, n);
  char *ptr3 = s21_memcpy(s3, s4, n);
  printf("%s\n%s\n%s\n", ptr1, ptr2, ptr3);

    return 0;
}