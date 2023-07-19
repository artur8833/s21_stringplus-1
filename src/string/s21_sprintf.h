#ifndef S_S21_SPRINTF_H_
#define S_S21_SPRINTF_H_
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>

typedef struct flags 
{

  int sign; //flag +
  int number;
  int wight; // если есть ширина то =1
  int num_wight; // значение ширины или точности
  int alignment;  //flag -
  int precision; // если есть '.'(точность), то флаг =1
  int num_wight2; // второе число после точки
  int flag_num2; // если есть второе число то =1
  int empty;

} structs;


int s21_putchar_to_str(const char c, char *str);

int convertNumberToChars(int number,char *str,structs *flags);

double roundToDec(double num,int dec);

void convertStringToString(char *s,char *str,structs *flags);

void convertCharToString(char c,char *str,structs *flags);

void convertfloatToString(double number,char *str,structs *flags);

int check_characteristics(const char c, va_list args, char *str,structs *flags);

int check_flags(const char c, char *str, structs *flags,int i,const char *format);

int file_wight( char *str, structs *flags, int i, const char *format);

int countDigits(float num, int precision);


#endif


