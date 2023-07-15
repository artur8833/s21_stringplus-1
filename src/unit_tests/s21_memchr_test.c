#include "s21_test.h"

START_TEST(memchrTest1) { 
  // NULL
  
  char* testStrValue1 = "qwe\0rty";
  int testIntValue1 = '\0';
  s21_size_t testCountValue1 = 0;

  char* testStrValue2 = "qazeDcrfv";
  int testIntValue2 = 'd';
  s21_size_t testCountValue2 = 10;

  char* testStrValue3 = "kekmem";
  int testIntValue3 = NULL;
  s21_size_t testCountValue3 = 4;

  char* testStrValue4 = "kek mem";
  int testIntValue4 = -1;
  s21_size_t testCountValue4 = 7;

  char* testStrValue5 = "kek\n mem";
  int testIntValue5 = 'n';
  s21_size_t testCountValue5 = 7;

  char* testStrValue6 = "memkek";
  int testIntValue6 = NULL;
  size_t testCountValue6 = NULL;

  ck_assert_ptr_eq(s21_memchr(testStrValue1, testIntValue1, testCountValue1), memchr(testStrValue1, testIntValue1, testCountValue1));
  ck_assert_ptr_eq(s21_memchr(testStrValue2, testIntValue2, testCountValue2), memchr(testStrValue2, testIntValue2, testCountValue2));
  ck_assert_ptr_eq(s21_memchr(testStrValue3, testIntValue3, testCountValue3), memchr(testStrValue3, testIntValue3, testCountValue3));
  ck_assert_ptr_eq(s21_memchr(testStrValue4, testIntValue4, testCountValue4), memchr(testStrValue4, testIntValue4, testCountValue4));
  ck_assert_ptr_eq(s21_memchr(testStrValue5, testIntValue5, testCountValue5), memchr(testStrValue5, testIntValue5, testCountValue5));
  ck_assert_ptr_eq(s21_memchr(testStrValue6, testIntValue6, testCountValue6), memchr(testStrValue6, testIntValue6, testCountValue6));
}
END_TEST;

START_TEST(memchrTest2) {
  // NORMAL 

  char* testStrValue1 = "qwe\0rty";
  int testIntValue1 = '\0';
  s21_size_t testCountValue1 = 10;

  char* testStrValue2 = "qazeDcrfv";
  int testIntValue2 = 'D';
  s21_size_t testCountValue2 = 5;

  char* testStrValue3 = "kekmem";
  int testIntValue3 = 'k';
  s21_size_t testCountValue3 = 1;

  char* testStrValue4 = "kek mem";
  int testIntValue4 = ' ';
  s21_size_t testCountValue4 = 13;

  char* testStrValue5 = "\n\n\n\n\n\n\n\n";
  int testIntValue5 = '\n';
  s21_size_t testCountValue5 = 13;

  char* testStrValue6 = "";
  int testIntValue6 = '\0';
  size_t testCountValue6 = 12;
  
  char* testStrValue7 = "nrqeyyyy";
  int testIntValue7 = 'y';
  size_t testCountValue7 = 5;

  ck_assert_ptr_eq(s21_memchr(testStrValue1, testIntValue1, testCountValue1), memchr(testStrValue1, testIntValue1, testCountValue1));
  ck_assert_ptr_eq(s21_memchr(testStrValue2, testIntValue2, testCountValue2), memchr(testStrValue2, testIntValue2, testCountValue2));
  ck_assert_ptr_eq(s21_memchr(testStrValue3, testIntValue3, testCountValue3), memchr(testStrValue3, testIntValue1, testCountValue3));
  ck_assert_ptr_eq(s21_memchr(testStrValue4, testIntValue4, testCountValue4), memchr(testStrValue4, testIntValue4, testCountValue4));
  ck_assert_ptr_eq(s21_memchr(testStrValue5, testIntValue5, testCountValue5), memchr(testStrValue5, testIntValue5, testCountValue5));
  ck_assert_ptr_eq(s21_memchr(testStrValue6, testIntValue6, testCountValue6), memchr(testStrValue6, testIntValue6, testCountValue6));
  ck_assert_ptr_eq(s21_memchr(testStrValue7, testIntValue7, testCountValue7), memchr(testStrValue7, testIntValue7, testCountValue7));
}
END_TEST;

Suite *memchrTest(void) {
  Suite *s = suite_create("\033[45mMemchr test\033[0m");
  TCase *tc = tcase_create("Memchr test");

  tcase_add_test(tc, memchrTest1);
  tcase_add_test(tc, memchrTest2);
  suite_add_tcase(s, tc);
  return s;
}
