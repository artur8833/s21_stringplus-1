#include "s21_test.h"

START_TEST(memcmpTest1) {
  size_t n0 = 0;
  size_t n4 = 4;
  size_t n7 = 7;
  size_t n12 = 12;

  const void *firstValueTest1 = "mem kek";
  const void *secondValueTest1 = "mem kek";

  const void *firstValueTest2 = "mem kek";
  const void *secondValueTest2 = "mem kek";

  const void *firstValueTest3 = "mem kek";
  const void *secondValueTest3 = "mem\n kek";

  const void *firstValueTest4 = "";
  const void *secondValueTest4 = "";

  const void *firstValueTest5 = "qwert ";
  const void *secondValueTest5 = "";

  const void *firstValueTest6 = "\n\n\n\n\n";
  const void *secondValueTest6 = "\n\n\n\n\n";

  const void *firstValueTest7 = "n n n n ";
  const void *secondValueTest7 = "n n N n ";

  const void *firstValueTest8 = "mem kek";
  const void *secondValueTest8 = "me\0m\n kek";

  const void *firstValueTest9 = "n";
  const void *secondValueTest9 = "n ";

  const void *firstValueTest10 = "";
  const void *secondValueTest10 = " ";
  
  ck_assert_int_eq(s21_memcmp(firstValueTest1, secondValueTest1, n12), memcmp(firstValueTest1, secondValueTest1, n12));
  ck_assert_int_eq(s21_memcmp(firstValueTest2, secondValueTest2, n0), memcmp(firstValueTest2, secondValueTest2, n0));
  ck_assert_int_eq(s21_memcmp(firstValueTest3, secondValueTest3, n4), memcmp(firstValueTest3, secondValueTest3, n4));
  ck_assert_int_eq(s21_memcmp(firstValueTest4, secondValueTest4, n12), memcmp(firstValueTest4, secondValueTest4, n12));
  ck_assert_int_eq(s21_memcmp(firstValueTest5, secondValueTest5, n12), memcmp(firstValueTest5, secondValueTest5, n12));
  ck_assert_int_eq(s21_memcmp(firstValueTest6, secondValueTest6, n12), memcmp(firstValueTest6, secondValueTest6, n12));
  ck_assert_int_eq(s21_memcmp(firstValueTest7, secondValueTest7, n12), memcmp(firstValueTest7, secondValueTest7, n12));
  ck_assert_int_eq(s21_memcmp(firstValueTest8, secondValueTest8, n7), memcmp(firstValueTest8, secondValueTest8, n7));
  ck_assert_int_eq(s21_memcmp(firstValueTest9, secondValueTest9, n7), memcmp(firstValueTest9, secondValueTest9, n7));
  ck_assert_int_eq(s21_memcmp(firstValueTest10, secondValueTest1, n0), memcmp(firstValueTest10, secondValueTest1, n0));
}
END_TEST;

START_TEST(memcmpTest2) {
  char* testStrValue1 = "asd";
  int testIntValue1 = 3;
  size_t testCountValue1 = 10;
  char* testStrValue2 = "asd";
  int testIntValue2 = 3;
  size_t testCountValue2 = 10;
  char* testStrValue3 = "asd";
  int testIntValue3 = 3;
  size_t testCountValue3 = 10;
  ck_assert_int_eq(s21_memcmp(testStrValue1, testIntValue1, testCountValue1), memcmp(testStrValue1, testIntValue1, testCountValue1));
  ck_assert_int_eq(s21_memcmp(testStrValue1, testIntValue1, testCountValue1), memcmp(testStrValue1, testIntValue1, testCountValue1));
  ck_assert_int_eq(s21_memcmp(testStrValue1, testIntValue1, testCountValue1), memcmp(testStrValue1, testIntValue1, testCountValue1));
}
END_TEST;

Suite *memcmpTest(void) {
  Suite *s = suite_create("\033[45mmemcmp test\033[0m");
  TCase *tc = tcase_create("memcmp test");

  tcase_add_test(tc, memcmpTest1);
  suite_add_tcase(s, tc);
  return s;
}