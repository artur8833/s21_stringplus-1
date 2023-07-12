#include "s21_string.h"

int main() {
  char str1[26] = "Hello, World! How are you?";
<<<<<<< HEAD
  char str2[] = "Hello";
=======
  char str2[] = "jkhads";
>>>>>>> c6a7ee1 (edit functions)

  // char str3[26] = "Hello, World! How are you?";
  // char str4[] = "Hella";

  size_t ptr1 = strcspn(str1, str2);
  // char *ptr2 = s21_strtok(str3, str4);

  // while(ptr1 != NULL){
  printf("    strtok:%ld\n", ptr1);
  // printf("s21_strtok:%s\n", ptr2);

    // ptr1 = strtok(NULL, str2);
  //   ptr2 = s21_strtok(NULL, str4);
  // }
  return 0;
}
