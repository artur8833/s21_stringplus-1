#include "s21_test.h"

START_TEST(strcmpTest1) {
  char* testStrValue1 = "";
  int testIntValue1 = 3;
  size_t testCountValue1 = 10;
  char* testStrValue2 = "";
  int testIntValue2 = 3;
  size_t testCountValue2 = 10;
  char* testStrValue3 = "";
  int testIntValue3 = 3;
  size_t testCountValue3 = 10;
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
}
END_TEST;

START_TEST(strcmpTest2) {
  char* testStrValue1 = "asd";
  int testIntValue1 = 3;
  size_t testCountValue1 = 10;
  char* testStrValue2 = "asd";
  int testIntValue2 = 3;
  size_t testCountValue2 = 10;
  char* testStrValue3 = "asd";
  int testIntValue3 = 3;
  size_t testCountValue3 = 10;
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
}
END_TEST;

START_TEST(strcmpTest2) {
  char* testStrValue1 = "memkek";
  int testIntValue1 = NULL;
  size_t testCountValue1 = NULL;
  char* testStrValue2 = "memkek";
  int testIntValue2 = NULL;
  size_t testCountValue2 = NULL;
  char* testStrValue3 = "memkek";
  int testIntValue3 = NULL;
  size_t testCountValue3 = NULL;
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
  ck_assert_char_eq(s21_strcmp(testStrValue1, testIntValue1), strcmp(testStrValue1, testIntValue1));
}
END_TEST;

Suite *strcmpTest(void) {
  Suite *s = suite_create("\033[45mStrcmp test\033[0m");
  TCase *tc = tcase_create("Strcmp test");

  tcase_add_test(tc, strcmpTest1);
  tcase_add_test(tc, strcmpTest2);
  suite_add_tcase(s, tc);
  return s;
}