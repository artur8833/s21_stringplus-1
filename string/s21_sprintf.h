#ifndef S_S21_SPRINTF_H_
#define S_S21_SPRINTF_H_
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

typedef struct flags {
  int sign;  // flag +
  int number;
  int wight;      // если есть ширина то =1
  int num_wight;  // значение ширины или точности
  int alignment;  // flag -
  int precision;  // если есть '.'(точность), то флаг =1
  int num_precision;
  int num_wight2;  // второе число после точки
  int flag_num2;   // если есть второе число то =1
  int empty;
  int flag_space;  //если есть пробел
  int flag_l;
  int flag_h;
  int negative_number;
  int flag_null;

} structs;

int s21_sprintf(char *str, const char *format, ...);

int s21_putchar_to_str(const char c, char *str);

void convertNumberToChars(char *str, structs *flags, long long number);

void convertUnsignedToChars(char *str, structs *flags,
                            unsigned long long number);

void convertfloatToString(char *str, structs *flags, va_list args);

void convertStringToString(char *str, structs *flags, va_list args);

void convertCharToString(char c, char *str, structs *flags);

void check_characteristics(const char c, va_list args, char *str,
                           structs *flags);

int check_flags(const char c, structs *flags, int i, const char *format);

int check_size(const char c, structs *flags, int i);

int parser_nums(structs *flags, int i, const char *format);

int parser_nums_point(structs *flags, int i, const char *format);

int countDigits(long double num, int precision);

void write_d(char *str, structs *flags, va_list args);

void write_u(char *str, structs *flags, va_list args);

#endif
