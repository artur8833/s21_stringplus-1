#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "s21_string.h"


int main() {
  char s1[] = "Hello, world!";
  char s2[] = "!";

  printf("%s", s21_strstr(s1, s2));


    return 0;
}