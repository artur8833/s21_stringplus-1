#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "s21_string.h"
struct Options{
  s21_size_t width;
  int length;
  int specifier;
  char *str_form;
};

void init_var(struct Options *, va_list Arg, char **src);
int s21_sscanf(const char *str, const char *format, ...);
int width_opt(struct Options *, char *f_p, char *src);
short int func_sh_int(char **src);
int func_int(char **src);
void *func_char(struct Options *opt, char **src);
char func_ch(char **src);
wchar_t func_wch(char **src);
float func_float(char **src);
double func_double(char **src);
long double func_Ldouble(char **src);
unsigned int func_uint(char **src);
unsigned short func_uhint(char **src);
void length_float_flags(struct Options *opt, va_list Arg, char **src);
void length_uint(struct Options *opt, va_list Arg, char **src);


// int main() {

//   char s1[20] = "\"(^-^)\"";
//   char s21_s1[20] = "\"(^-^)\"";
//   long double f1, s21_f1;
//   int x = 0, y = 0;
//   char c1;
//   char s21_c1;
//   wchar_t c2, s21_c2;
//   unsigned int x1, y1;
//   unsigned short int x2 = 0, y2 = 0;


//   char *str = "256.34e-5faasd523f 00000176 087Asdf ";
//   sscanf(str, "%Lf %5s %d %c %lc %o %ho", &f1, s1, &x, &c1, &c2, &x1, &x2);
//   s21_sscanf(str, "%Lf %5s %d %c %lc %o %ho", &s21_f1, s21_s1, &y, &s21_c1, &s21_c2, &y1, &y2);
//   printf("    sscanf:%Lf\n    sscanf:%s\n    sscanf:%d\n    sscanf:%c\n    sscanf:%lc\n    sscanf:%o\n    sscanf:%ho\n", f1, s1, x, c1, c2, x1, x2);
//   printf("s21_sscanf:%Lf\ns21_sscanf:%s\ns21_sscanf:%d\ns21_sscanf:%c\ns21_sscanf:%lc\ns21_sscanf:%o\ns21_sscanf:%ho\n", s21_f1, s21_s1, y, s21_c1, s21_c2, y1, y2);
//   return 0;
// }

int width_opt(struct Options *opt, char *f_p, char *src){
  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_f_p = s21_strcspn(f_p, "1234567890");
  s21_size_t x = atoi(f_p);
  if(x > len_src){
    opt->width += len_src;
  } else opt->width += x;

  return len_f_p - 1;
}

int s21_sscanf(const char *str, const char *format, ...) {
  char *spec = "cdieEfgGosuxXpn%";
  char *src = (char *)str;
  char **s = &src;
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
      opt.length = *f_p;
    } else if(s21_strchr(spec, *f_p)){
      opt.specifier = *f_p;
      init_var(&opt, Arg, s);
      printf("\t%s\n", *s);
    }
    f_p++;
	} 

  if(*f_p != '\0') f_p++;
  va_end(Arg);
  return 0;
}

void length_char(struct Options *opt, va_list Arg, char **src){
  if(opt->length == 0){
    char *ch = va_arg(Arg, char *);
    *ch = func_ch(src);
  } else if(opt->length == 'l'){
    wchar_t *wch = va_arg(Arg, wchar_t *);
    *wch = func_wch(src);
    opt->length = 0;
  }
}

void length_uint(struct Options *opt, va_list Arg, char **src){
  if(opt->length == 0){
    unsigned int *o = va_arg(Arg, unsigned int *);
    *o = func_uint(src);
  } else if(opt->length == 'h'){
    unsigned short *ho = va_arg(Arg, unsigned short *);
    *ho = func_uhint(src);
    opt->length = 0;
  }
}

void length_int(struct Options *opt, va_list Arg, char **src){
  if(opt->length == 0){
    int *d = va_arg(Arg, int *);
    *d = func_int(src);
  } else if(opt->length == 'h'){
    short int *hd = va_arg(Arg, short int *);
    *hd = func_sh_int(src);
    opt->length = 0;
  }
}

void length_float_flags(struct Options *opt, va_list Arg, char **src){
  if(opt->length == 'L'){
    long double *lde = va_arg(Arg, long double *);
    *lde = func_Ldouble(src);
    opt->length = 0;
  } else if(opt->length == 'l'){
    double *de = va_arg(Arg, double *);
    *de = func_double(src);
    opt->length = 0;
  } else if(opt->length == 0){
    float *ft = va_arg(Arg, float *);
    *ft = func_float(src);
  }
}

void init_var(struct Options *opt, va_list Arg, char **src) {

    switch (opt->specifier) {
    case 'c': // символ l
      length_char(opt, Arg, src);
      break;
    case 'd': // знаковое десятичное целое число h
      length_int(opt, Arg, src);
      break;
    case 'i': // знаковое целое число (можэт быть десятичным, восьмеричным или h
              // шестнадцатиричным)
      length_int(opt, Arg, src);
      break;
    case 'e': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      length_float_flags(opt, Arg, src);
      break;
    case 'E': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      length_float_flags(opt, Arg, src);
      break;
    case 'f': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      length_float_flags(opt, Arg, src);
      break;
    case 'g': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      length_float_flags(opt, Arg, src);
      break;
    case 'G': // десятичное число с плавающей точкой или научная нотация L
              // (мантиса/экспонента)
      length_float_flags(opt, Arg, src);
      break;
    case 'o': // беззнаковое восьмеричное число h
      length_uint(opt, Arg, src);
      break;
    case 's': // строка символов l
      char *s = (char*)va_arg(Arg, char *);
      char *str = func_char(opt, src);
      str = s21_memcpy(s, str, opt->width + 1);
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

unsigned int func_uint(char **src){
  char mass[256];
  s21_size_t len_mas = s21_strcspn(*src, "1234567890");
  s21_memcpy(mass, *src, len_mas);
  mass[len_mas] = '\0';
  unsigned long int x = strtoul(mass, src, 0);
    printf("%s", *src);
  *src = *src + len_mas;

  return (unsigned int)x;
}

unsigned short int func_uhint(char **src){
  char mass[256];
  s21_size_t len_mas = s21_strcspn(*src, "1234567890");
  s21_memcpy(mass, *src, len_mas);
  mass[len_mas] = '\0';
  unsigned long int x = strtoul(*src, src, 0);
  printf("%s", *src);
  *src = *src + len_mas;

  return (unsigned short int)x;
}

wchar_t func_wch(char **src){
  wchar_t ch = '0';
  while(**src == ' ' && **src != '\0'){
    *src = *src + 1;
  }
  if(**src != '\0'){
    ch = **src;
    *src = *src + 1;
  }
  return ch;
}

char func_ch(char **src){
  char ch = '0';
  while(**src == ' ' && **src != '\0'){
    *src = *src + 1;
  }
  if(**src != '\0'){
    ch = **src;
    *src = *src + 1;
  }
  return ch;
}

short int func_sh_int(char **src){
  char mass[256];
  s21_size_t len_mas = s21_strcspn(*src, "1234567890");
  s21_memcpy(mass, *src, len_mas);
  mass[len_mas] = '\0';
  *src = *src + len_mas;

  return atoi(mass);
}

int func_int(char **src){
	char mass[256];
  s21_size_t len_mas = s21_strcspn(*src, "1234567890");
  s21_memcpy(mass, *src, len_mas);
  mass[len_mas] = '\0';
  *src = *src + len_mas;

  return atoi(mass);
}

void *func_char(struct Options *opt, char **src){
  static char mass[1024];
  s21_memcpy(mass, *src, opt->width);
  mass[opt->width] = '\0';
  *src = *src + opt->width;

  return (void*)mass;
}

float func_float(char **src){
	float mass;
  mass = strtof(*src, src);

  return mass;
}

double func_double(char **src){
	double mass;
  mass = strtod(*src, src);

  return mass;
}

long double func_Ldouble(char **src){
	long double mass;
  mass = strtold(*src, src);

  return mass;
}