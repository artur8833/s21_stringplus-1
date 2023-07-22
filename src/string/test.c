#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "s21_string.h"

// short atoh(char);
// int atoi(char);
// long atol(char);
// long long atoll(char);
// double stod(char *);
// float stof(char *);
// long double stold(char *);
struct Options{
  s21_size_t width;
  int length;
  int specifier;
  char *str_form;
};

void init_var(struct Options, va_list Arg, char *src);
int s21_sscanf(const char *str, const char *format, ...);
int width_opt(struct Options *, char *, char *);

int func_int(struct Options, va_list Arg, char *src);
void *func_char(struct Options, va_list Arg, char *src);


int main() {

  char s1[20] = "\"(^-^)\"";
  char s21_s1[20] = "\"(^-^)\"";
  // float f1, s21_f1;
  int i1 = 0, s21_i1 = 0;

  char *str = "256asddsfaasdfasdf";
  // sscanf(str, "%12s", s1);
  s21_sscanf(str, "%12s", s21_s1);
  printf("%s\n", s21_s1);
  return 0;
}

int func_int(struct Options opt, va_list Arg, char *src){
	static char mass[256];
  s21_size_t len_mas = s21_strspn(src, "1234567890");
  s21_memcpy(mass, src, len_mas);
  mass[len_mas] = '\0';
  return atoi(mass);
}

void *func_char(struct Options opt, va_list Arg, char *src){
  static char mass[1024];
  s21_memcpy(mass, src, opt.width);
  mass[opt.width] = '\0';
  return (void*)mass;
}

int width_opt(struct Options *opt, char *f_p, char *src){
  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_f_p = s21_strspn(f_p, "1234567890");
  s21_size_t x = atoi(f_p);
  if(x > len_src){
    opt->width += len_src;
  } else opt->width += x;

  return len_f_p - 1;
}

int s21_sscanf(const char *str, const char *format, ...) {
  char *spec = "cdieEfgGosuxXpn%";
  char *src = (char *)str;
  char *f_p = (char *)format;
  va_list Arg;
  va_start(Arg, format);
  struct Options opt = {0};
  while(*f_p != '\0'){
    if (*f_p == '%'){
      f_p++;
    } 
    if(isdigit(*f_p)){
      f_p += width_opt(&opt, f_p, src);
    } else if(s21_strchr("hlL", *f_p)){
      opt.length = 1;
    } else if(s21_strchr(spec, *f_p)){
      opt.specifier = *f_p;
      init_var(opt, Arg, src);
    }
    f_p++;
	} 

    if(*f_p != '\0') f_p++;

  
  va_end(Arg);
  return 0;
}


void init_var(struct Options opt, va_list Arg, char *src) {

    switch (opt.specifier) {
    // case 'c': // символ l
    //   break;
    case 'd': // знаковое десятичное целое число h
      int *d = va_arg(Arg, int *);
      *d = func_int(opt, Arg, src);
      break;
    case 'i': // знаковое целое число (можэт быть десятичным, восьмеричным или h
              // шестнадцатиричным)
      int *i = va_arg(Arg, int *);
      *i = func_int(opt, Arg, src);
      break;
    case 'e': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      break;
    case 'E': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      break;
    case 'f': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      break;
    case 'g': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      break;
    case 'G': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      break;
    case 'o': // беззнаковое восьмеричное число h
      break;
    case 's': // строка символов l
    char *s = (char*)va_arg(Arg, char *);
    char *str = func_char(opt, Arg, src);
    str = s21_memcpy(s, str, opt.width + 1);
          printf("%s\n", src);

      break;
    case 'u': // беззнаковое десятичное целое число h
      break;
    case 'x': // беззнаковое шестнадцатиричное целое число (любые буквы) h
      break;
    case 'X': // беззнаковое шестнадцатиричное целое число (любые буквы) h
      break;
    case 'p': // адрес указателя
      break;
    case 'n': // количество символов, считанных до появления %n
      break;
    case '%': // символ %
    }
  }





