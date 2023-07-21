#ifndef S_S21_SPRINTF_H_
#define S_S21_SPRINTF_H_
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <ctype.h>

typedef struct flags 
{

  int sign;
  int number;
  int wight;
  int num_wight;
  int float_flag;
  int alignment;

} structs;


int s21_putchar_to_str(const char c, char *str);
int convertNumberToChars(int number,char *str,structs *flags);
double roundToDec(double num,int dec);
void convertStringToString(char *s,char *str);
void convertfloatToString(double number,char *str,int precision,structs *flags);
int check_characteristics(const char c, va_list args, char *str,structs *flags);
int check_flags(const char c, char *str, structs *flags,int i,const char *format);
int file_wight( char *str, structs *flags, int i, const char *format);


#endif


