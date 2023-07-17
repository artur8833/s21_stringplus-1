#include "s21_test.h"




START_TEST(strcatTest1) {
  char* testStrValue1 = "";
  int testIntValue1 = 3;
  size_t testCountValue1 = 10;
  char* testStrValue2 = "";
  int testIntValue2 = 3;
  size_t testCountValue2 = 10;
  char* testStrValue3 = "";
  int testIntValue3 = 3;
  size_t testCountValue3 = 10;
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
}
END_TEST;

START_TEST(strcatTest2) {
  char* testStrValue1 = "asd";
  int testIntValue1 = 3;
  size_t testCountValue1 = 10;
  char* testStrValue2 = "asd";
  int testIntValue2 = 3;
  size_t testCountValue2 = 10;
  char* testStrValue3 = "asd";
  int testIntValue3 = 3;
  size_t testCountValue3 = 10;
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
}
END_TEST;

START_TEST(strcatTest2) {
  char* testStrValue1 = "memkek";
  int testIntValue1 = NULL;
  size_t testCountValue1 = NULL;
  char* testStrValue2 = "memkek";
  int testIntValue2 = NULL;
  size_t testCountValue2 = NULL;
  char* testStrValue3 = "memkek";
  int testIntValue3 = NULL;
  size_t testCountValue3 = NULL;
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcat(testStrValue1, testIntValue1), strcat(testStrValue1, testIntValue1));
}
END_TEST;

Suite *strcatTest(void) {
  Suite *s = suite_create("\033[45mStrcat test\033[0m");
  TCase *tc = tcase_create("Strcat test");

  tcase_add_test(tc, strcatTest1);
  tcase_add_test(tc, strcatTest2);
  suite_add_tcase(s, tc);
  return s;
}