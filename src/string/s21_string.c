#include "s21_string.h"

int main() {
  char str1[26] = "Hello, World! How are you?";
  char str2[] = "Hella";

  char str3[26] = "Hello, World! How are you?";
  char str4[] = "Hella";

  char *ptr1 = strtok(str1, str2);
  char *ptr2 = s21_strtok(str3, str4);

  printf("    strtok:%s\n", ptr1);
  printf("s21_strtok:%s\n", ptr2);

  return 0;
}
