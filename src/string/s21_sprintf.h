#ifndef S_S21_SPRINTF_H_
#define S_S21_SPRINTF_H_
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include<limits.h>

typedef struct flags 
{

  int sign; //flag +
  int number;
  int wight; // если есть ширина то =1
  int num_wight; // значение ширины или точности
  int alignment;  //flag -
  int precision; // если есть '.'(точность), то флаг =1
  int num_precision;
  int num_wight2; // второе число после точки
  int flag_num2; // если есть второе число то =1
  int empty;
  int flag_space; //еслие сть пробел
  int flag_l;
  int flag_h;

} structs;


int s21_putchar_to_str(const char c, char *str);

int convertNumberToChars(char *str,structs *flags, va_list args);

void convertfloatToString(char *str,structs *flags,va_list args);

double roundToDec(double num,int dec);

void convertStringToString(char *str,structs *flags,va_list args);

void convertCharToString(char c,char *str,structs *flags);

int check_characteristics(const char c, va_list args, char *str,structs *flags);

int check_flags(const char c, char *str, structs *flags,int i,const char *format);

int check_size(const char c, char *str, structs *flags,int i,const char *format);

int parser_nums(char *str, structs *flags, int i, const char *format);

int parser_nums_point( char *str, structs *flags, int i, const char *format);

int countDigits(long double num, int precision);

int converFarmat( long double number, structs *flags );


#endif


