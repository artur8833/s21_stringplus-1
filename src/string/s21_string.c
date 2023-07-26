#include "s21_string.h"

int main() {
  char s1[] = "ROROROROMA!!!!!!!!!";
  char s2[] = "ROROROROMA!!!!!!!!!";
  char s3[] = "R";
  
  strtok(s1, s3);
  s21_strtok(s2, s3);
  

    strtok(NULL, s3);
  s21_strtok(NULL, s3);
    printf("    strtok:%s\n", s1);
    printf("s21_strtok:%s\n", s2);
 

  // ck_assert_pstr_eq(strtok(s3, s6), s21_strtok(s4, s6));
  // ck_assert_pstr_eq(strtok(NULL, s6), s21_strtok(NULL, s6));
  // ck_assert_pstr_eq(strtok(NULL, s6), s21_strtok(NULL, s6));
  // char *ptr1 = strtok(str1, str3);
  // char *ptr2 = s21_strtok(str2, str3);

  // while (ptr1 != S21_NULL) {

  //   ptr1 = strtok(S21_NULL, str2);
  //   ptr2 = s21_strtok(S21_NULL, str4);
  // }
  return 0;
}
