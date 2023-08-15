#include "s21_test.h"

START_TEST(insertTest1) {
  const char *src = "Hello, world!";
  const char *str = "beautiful ";
  s21_size_t start_index = 7;
  void *result = s21_insert(src, str, start_index);

  char *inserted_str = (char *)result;
  ck_assert_str_eq(inserted_str, "Hello, beautiful world!");

  free(inserted_str);
}
END_TEST

START_TEST(insertTest2) {
  const char *src = "";
  const char *str = "";
  s21_size_t start_index = 20;
  void *result = s21_insert(src, str, start_index);

  free(result);
}
END_TEST

START_TEST(insertTest3) {
  const char *src = NULL;
  const char *str = "Hello";
  s21_size_t start_index = 0;
  void *result = s21_insert(src, str, start_index);

  free(result);
}
END_TEST

Suite *insertTest(void) {
  Suite *s = suite_create("\033[45mInsert test\033[0m");
  TCase *tc = tcase_create("Core of s21_string");

  tcase_add_test(tc, insertTest1);
  tcase_add_test(tc, insertTest2);
  tcase_add_test(tc, insertTest3);

  suite_add_tcase(s, tc);
  return s;
}
