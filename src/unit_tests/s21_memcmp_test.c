#include "s21_test.h"

START_TEST(memcmpTest1) {
  const void *firstValueTest1 = "mem kek";
  const void *secondValueTest1 = "mem kek";
  s21_size_t n = 12;

  ck_assert_int_eq(s21_memcmp(firstValueTest1, secondValueTest1, n),
                   memcmp(firstValueTest1, secondValueTest1, n));
}
END_TEST

START_TEST(memcmpTest2) {
  const void *firstValueTest2 = "mem kek";
  const void *secondValueTest2 = "mem kek";
  s21_size_t n = 0;

  ck_assert_int_eq(s21_memcmp(firstValueTest2, secondValueTest2, n),
                   memcmp(firstValueTest2, secondValueTest2, n));
}

START_TEST(memcmpTest3) {
  const void *firstValueTest3 = "mem kek";
  const void *secondValueTest3 = "mem\n kek";
  s21_size_t n = 5;

  ck_assert_int_eq(s21_memcmp(firstValueTest3, secondValueTest3, n),
                   memcmp(firstValueTest3, secondValueTest3, n));
}

START_TEST(memcmpTest4) {
  const void *firstValueTest4 = "";
  const void *secondValueTest4 = "";
  s21_size_t n = 12;

  ck_assert_int_eq(s21_memcmp(firstValueTest4, secondValueTest4, n),
                   memcmp(firstValueTest4, secondValueTest4, n));
}

START_TEST(memcmpTest5) {
  const void *firstValueTest5 = "qwert ";
  const void *secondValueTest5 = "";
  s21_size_t n = 12;

  ck_assert_int_eq(s21_memcmp(firstValueTest5, secondValueTest5, n),
                   memcmp(firstValueTest5, secondValueTest5, n));
}

START_TEST(memcmpTest6) {
  const void *firstValueTest6 = "\n\n\n\n\n";
  const void *secondValueTest6 = "\n\n\n\n\n";
  s21_size_t n = 12;

  ck_assert_int_eq(s21_memcmp(firstValueTest6, secondValueTest6, n),
                   memcmp(firstValueTest6, secondValueTest6, n));
}

START_TEST(memcmpTest7) {
  const void *firstValueTest7 = "n n n n ";
  const void *secondValueTest7 = "n n N n ";
  s21_size_t n = 12;

  ck_assert_int_eq(s21_memcmp(firstValueTest7, secondValueTest7, n),
                   memcmp(firstValueTest7, secondValueTest7, n));
}

START_TEST(memcmpTest8) {
  const void *firstValueTest8 = "mem kek";
  const void *secondValueTest8 = "me\0m\n kek";
  s21_size_t n = 7;

  ck_assert_int_eq(s21_memcmp(firstValueTest8, secondValueTest8, n),
                   memcmp(firstValueTest8, secondValueTest8, n));
}

START_TEST(memcmpTest9) {
  const void *firstValueTest9 = "n";
  const void *secondValueTest9 = "n ";
  s21_size_t n = 7;

  ck_assert_int_eq(s21_memcmp(firstValueTest9, secondValueTest9, n),
                   memcmp(firstValueTest9, secondValueTest9, n));
}

START_TEST(memcmpTest10) {
  const void *firstValueTest10 = "";
  const void *secondValueTest10 = " ";
  s21_size_t n = 0;

  ck_assert_int_eq(s21_memcmp(firstValueTest10, secondValueTest10, n),
                   memcmp(firstValueTest10, secondValueTest10, n));
}

Suite *memcmpTest(void) {
  Suite *s = suite_create("\033[45mMemcmp test\033[0m");
  TCase *tc = tcase_create("Memcmp test");

  tcase_add_test(tc, memcmpTest1);
  tcase_add_test(tc, memcmpTest2);
  tcase_add_test(tc, memcmpTest3);
  tcase_add_test(tc, memcmpTest4);
  tcase_add_test(tc, memcmpTest5);
  tcase_add_test(tc, memcmpTest6);
  tcase_add_test(tc, memcmpTest7);
  tcase_add_test(tc, memcmpTest8);
  tcase_add_test(tc, memcmpTest9);
  tcase_add_test(tc, memcmpTest10);

  suite_add_tcase(s, tc);

  return s;
}