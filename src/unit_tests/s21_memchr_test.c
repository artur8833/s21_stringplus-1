#include "s21_test.h"

START_TEST(memchrTest1) {
  char* strValue = "qwe\0rty";
  s21_size_t countValue = 0;

  ck_assert_ptr_eq(s21_memchr(strValue, '\0', countValue),
                   memchr(strValue, '\0', countValue));
}
END_TEST

START_TEST(memchrTest2) {
  char* strValue = "qazeDcrfv";
  s21_size_t countValue = 10;

  ck_assert_ptr_eq(s21_memchr(strValue, 'd', countValue),
                   memchr(strValue, 'd', countValue));
}

START_TEST(memchrTest3) {
  char* strValue = "kekmem";
  s21_size_t countValue = 4;

  ck_assert_ptr_eq(s21_memchr(strValue, 101, countValue),
                   memchr(strValue, 101, countValue));
}

START_TEST(memchrTest4) {
  char* strValue = "kek mem";
  s21_size_t countValue = 7;

  ck_assert_ptr_eq(s21_memchr(strValue, 0, countValue),
                   memchr(strValue, 0, countValue));
}

START_TEST(memchrTest5) {
  char* strValue = "memkek";
  size_t countValue = 0;

  ck_assert_ptr_eq(s21_memchr(strValue, 0, countValue),
                   memchr(strValue, 0, countValue));
}

START_TEST(memchrTest6) {
  char* strValue = "kek\n mem";
  s21_size_t countValue = 7;

  ck_assert_ptr_eq(s21_memchr(strValue, 'n', countValue),
                   memchr(strValue, 'n', countValue));
}

START_TEST(memchrTest7) {
  char* strValue = "qwe\0rty";
  s21_size_t countValue = 10;

  ck_assert_ptr_eq(s21_memchr(strValue, '\0', countValue),
                   memchr(strValue, '\0', countValue));
}

START_TEST(memchrTest8) {
  char* strValue = "qazeDcrfv";
  s21_size_t countValue = 5;

  ck_assert_ptr_eq(s21_memchr(strValue, 'D', countValue),
                   memchr(strValue, 'D', countValue));
}

START_TEST(memchrTest9) {
  char* strValue = "kekmem";
  s21_size_t countValue = 1;

  ck_assert_ptr_eq(s21_memchr(strValue, 'k', countValue),
                   memchr(strValue, 'k', countValue));
}

START_TEST(memchrTest10) {
  char* strValue = "kek mem";
  s21_size_t countValue = 13;

  ck_assert_ptr_eq(s21_memchr(strValue, ' ', countValue),
                   memchr(strValue, ' ', countValue));
}

START_TEST(memchrTest11) {
  char* strValue = "\n\n\n\n\n\n\n\n";
  s21_size_t countValue = 13;

  ck_assert_ptr_eq(s21_memchr(strValue, '\n', countValue),
                   memchr(strValue, '\n', countValue));
}

START_TEST(memchrTest12) {
  char* strValue = "";
  size_t countValue = 12;

  ck_assert_ptr_eq(s21_memchr(strValue, '\0', countValue),
                   memchr(strValue, '\0', countValue));
}

START_TEST(memchrTest13) {
  char* strValue = "nrqeyyyy";
  size_t countValue = 5;

  ck_assert_ptr_eq(s21_memchr(strValue, 'y', countValue),
                   memchr(strValue, 'y', countValue));
}

Suite* memchrTest(void) {
  Suite* s = suite_create("\033[45mMemchr test\033[0m");
  TCase* tc = tcase_create("Memchr test");

  tcase_add_test(tc, memchrTest1);
  tcase_add_test(tc, memchrTest2);
  tcase_add_test(tc, memchrTest3);
  tcase_add_test(tc, memchrTest4);
  tcase_add_test(tc, memchrTest5);
  tcase_add_test(tc, memchrTest6);
  tcase_add_test(tc, memchrTest7);
  tcase_add_test(tc, memchrTest8);
  tcase_add_test(tc, memchrTest9);
  tcase_add_test(tc, memchrTest10);
  tcase_add_test(tc, memchrTest11);
  tcase_add_test(tc, memchrTest12);
  tcase_add_test(tc, memchrTest13);

  suite_add_tcase(s, tc);

  return s;
}
