#include "s21_test.h"

START_TEST(strerror_1) {
  char *case1 = s21_strerror(0);
  char *case2 = strerror(0);
  ck_assert_uint_eq((unsigned long)*case1, (unsigned long)*case2);

  char *case9 = s21_strerror(1);
  char *case10 = strerror(1);
  ck_assert_uint_eq((unsigned long)*case9, (unsigned long)*case10);

  char *case0 = s21_strerror(106);
  char *case3 = strerror(106);
  ck_assert_uint_eq((unsigned long)*case0, (unsigned long)*case3);

  char *case7 = s21_strerror(200);
  char *case8 = strerror(200);
  ck_assert_uint_eq((unsigned long)*case7, (unsigned long)*case8);

  char *case11 = s21_strerror(-1);
  char *case12 = strerror(-1);
  ck_assert_uint_eq((unsigned long)*case11, (unsigned long)*case12);
}
END_TEST

Suite *strerrorTest(void) {
  Suite *s = suite_create("\033[45msuite_strerror\033[0m");
  TCase *tc = tcase_create("strerror_tc");
  tcase_add_test(tc, strerror_1);
  suite_add_tcase(s, tc);
  return s;
}
