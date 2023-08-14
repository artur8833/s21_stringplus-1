#include "s21_test.h"

START_TEST(toupperTest1) {
  char str1[] = "school";
  ck_assert_str_eq(s21_to_upper(str1), "SCHOOL");
}
END_TEST

START_TEST(toupperTest2) {
  char str2[] = "school_21/";
  ck_assert_str_eq(s21_to_upper(str2), "SCHOOL_21/");
}
END_TEST

START_TEST(toupperTest3) {
  char str3[] = "";
  ck_assert_str_eq(s21_to_upper(str3), "");
}
END_TEST

START_TEST(toupperTest4) {
  char str4[] = "12345";
  ck_assert_str_eq(s21_to_upper(str4), "12345");
}
END_TEST

START_TEST(toupperTest5) {
  char str5[] = "aBcDeFgH";
  ck_assert_str_eq(s21_to_upper(str5), "ABCDEFGH");
}
END_TEST

START_TEST(toupperTest6) {
  char str6[] = "Hello World!";
  ck_assert_str_eq(s21_to_upper(str6), "HELLO WORLD!");
}
END_TEST

START_TEST(toupperTest7) {
  const char *str7 = NULL;
  ck_assert_ptr_null(s21_to_upper(str7));
}
END_TEST

Suite *toupperTest(void) {
  Suite *s = suite_create("\033[45mto upper Test\033[0m");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, toupperTest1);
  tcase_add_test(tc, toupperTest2);
  tcase_add_test(tc, toupperTest3);
  tcase_add_test(tc, toupperTest4);
  tcase_add_test(tc, toupperTest5);
  tcase_add_test(tc, toupperTest6);
  tcase_add_test(tc, toupperTest7);

  suite_add_tcase(s, tc);
  return s;
}
