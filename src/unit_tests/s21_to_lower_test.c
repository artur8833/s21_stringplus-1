#include "s21_test.h"

START_TEST(tolowerTest1) {
  char str1[] = "SCHOOL!";
  ck_assert_str_eq(s21_to_lower(str1), "school!");
}
END_TEST

START_TEST(tolowerTest2) {
  char str2[] = "SCHOOL_21/";
  ck_assert_str_eq(s21_to_lower(str2), "school_21/");
}
END_TEST

START_TEST(tolowerTest3) {
  char str3[] = "";
  ck_assert_str_eq(s21_to_lower(str3), "");
}
END_TEST

START_TEST(tolowerTest4) {
  const char *str5 = S21_NULL;
  ck_assert_ptr_null(s21_to_lower(str5));
}
END_TEST

Suite *tolowerTest(void) {
  Suite *s = suite_create("\033[45mto lower Test\033[0m");
  TCase *tc = tcase_create("to_lower_tc");

  tcase_add_test(tc, tolowerTest1);
  tcase_add_test(tc, tolowerTest2);
  tcase_add_test(tc, tolowerTest3);
  tcase_add_test(tc, tolowerTest4);

  suite_add_tcase(s, tc);
  return s;
}
