#include "s21_test.h"

#define BUFF_SIZE 512

START_TEST(simple_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "This is a simple value %d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(plus_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+12d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(zero_precision_zero_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.0d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(space_flag_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_val_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(unsigned_val_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% 5.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% -5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'c', 'c', 'c'),
                   sprintf(str2, format, val, 'c', 'c', 'c', 'c'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(one_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(string_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(string_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";

  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(all_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(empty_format_and_parameters) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                   sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
                   sprintf(str2, "%s", "Drop Sega PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(

      s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
      sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d %d %+d %d", 666, 0, 234, -98),
                   sprintf(str2, "%d %d %+d %d", 666, 0, 234, -98));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%d%d%d%d%3d%-2d%-4.5d", -999, 0, 666, -100, 0, 77, 98),
      sprintf(str2, "%d%d%d%d%3d%-2d%-4.5d", -999, 0, 666, -100, 0, 77, 98));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_float) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                   sprintf(str2, "%f", 0.0001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                   sprintf(str2, "%u", (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100),
                   sprintf(str2, "%u%u%u%u", (unsigned)999, (unsigned)0,
                           (unsigned)666, (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_one_char_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'),
                   sprintf(str2, "%-8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_many_char_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'),
      sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(proc) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "Hello %%"), sprintf(str2, "Hello %%"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hu";
  ck_assert_int_eq(s21_sprintf(str1, format, 1234),
                   sprintf(str2, format, 1234));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsigned_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello %Lu";
  ck_assert_int_eq(s21_sprintf(str1, format, 3434343434343),
                   sprintf(str2, format, 3434343434343));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world %ld";
  ck_assert_int_eq(s21_sprintf(str1, format, -3778467368176),
                   sprintf(str2, format, -3778467368176));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world %hd";
  ck_assert_int_eq(s21_sprintf(str1, format, 132), sprintf(str2, format, 132));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_space_minus) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world %- d";
  ck_assert_int_eq(s21_sprintf(str1, format, 22), sprintf(str2, format, 22));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_minus) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world and world %f";
  ck_assert_int_eq(s21_sprintf(str1, format, -33.4),
                   sprintf(str2, format, -33.4));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsign_mminus) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world and world %-u";
  ck_assert_int_eq(s21_sprintf(str1, format, 787878),
                   sprintf(str2, format, 787878));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_wight) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world and world %+4.8f";
  ck_assert_int_eq(s21_sprintf(str1, format, 7.87878),
                   sprintf(str2, format, 7.87878));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_wight2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world and world %4.15f %lf";
  ck_assert_int_eq(s21_sprintf(str1, format, 7.83232, 78787979.7899),
                   sprintf(str2, format, 7.83232, 78787979.7899));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(float_sign) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world and world %-4.15f %-4.15f";
  ck_assert_int_eq(s21_sprintf(str1, format, 7.83232, -5.3232),
                   sprintf(str2, format, 7.83232, -5.3232));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(unsign_wight) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hello world and world %-4.15u";
  ck_assert_int_eq(s21_sprintf(str1, format, 783232),
                   sprintf(str2, format, 783232));

  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *sprintfTest(void) {
  Suite *s = suite_create("\033[45mSprintf test\033[0m");
  TCase *tc = tcase_create("Sprintf test");

  tcase_add_test(tc, simple_int);
  tcase_add_test(tc, width_int);
  tcase_add_test(tc, plus_width_int);
  tcase_add_test(tc, zero_precision_zero_int);
  tcase_add_test(tc, space_flag_int);
  tcase_add_test(tc, unsigned_val);
  tcase_add_test(tc, unsigned_val_width);
  tcase_add_test(tc, unsigned_val_flags);
  tcase_add_test(tc, unsigned_val_precision);
  tcase_add_test(tc, unsigned_val_many_flags);
  tcase_add_test(tc, unsigned_zero);
  tcase_add_test(tc, one_precision);
  tcase_add_test(tc, one_flags);
  tcase_add_test(tc, one_width);
  tcase_add_test(tc, one_many);
  tcase_add_test(tc, one_many_flags);
  tcase_add_test(tc, string);
  tcase_add_test(tc, string_precision);
  tcase_add_test(tc, string_width);
  tcase_add_test(tc, string_flags);
  tcase_add_test(tc, string_long);
  tcase_add_test(tc, string_many);
  tcase_add_test(tc, float_flags);
  tcase_add_test(tc, all_empty);
  tcase_add_test(tc, empty_format_and_parameters);
  tcase_add_test(tc, test_one_char);
  tcase_add_test(tc, test_many_char);
  tcase_add_test(tc, test_one_string);
  tcase_add_test(tc, test_many_string);
  tcase_add_test(tc, test_one_dec);
  tcase_add_test(tc, test_many_dec);
  tcase_add_test(tc, test_one_float);
  tcase_add_test(tc, test_one_unsigned_dec);
  tcase_add_test(tc, test_many_unsigned_dec);
  tcase_add_test(tc, test_one_char_with_alignment_left);
  tcase_add_test(tc, test_one_char_with_alignment_right);
  tcase_add_test(tc, test_many_char_with_alignment);
  tcase_add_test(tc, proc);
  tcase_add_test(tc, unsigned_short);
  tcase_add_test(tc, unsigned_long);
  tcase_add_test(tc, int_long);
  tcase_add_test(tc, int_short);
  tcase_add_test(tc, int_space_minus);
  tcase_add_test(tc, float_minus);
  tcase_add_test(tc, unsign_mminus);
  tcase_add_test(tc, float_wight);
  tcase_add_test(tc, float_wight2);
  tcase_add_test(tc, float_sign);
  tcase_add_test(tc, unsign_wight);
  suite_add_tcase(s, tc);
  return s;
}