#include "s21_test.h"

START_TEST(trim1) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(trim2) {
  const char *src = "   \t   Trim \t Test   \t   ";
  const char *trim_chars = " \t";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Trim \t Test");
  free(result);
}
END_TEST

START_TEST(trim3) {
  const char *src = "Hello, World!";
  const char *trim_chars = "";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(trim4) {
  const char *src = "  Hello, World!!!!  ";
  const char *trim_chars = S21_NULL;
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!!!!");
  free(result);
}
END_TEST

START_TEST(trim5) {
  const char *src = NULL;
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_ptr_null(result);
}
END_TEST

Suite *trimTest(void) {
  Suite *s = suite_create("\033[45mtrim Test\033[0m");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, trim1);
  tcase_add_test(tc, trim2);
  tcase_add_test(tc, trim3);
  tcase_add_test(tc, trim4);
  tcase_add_test(tc, trim5);

  suite_add_tcase(s, tc);
  return s;
}
