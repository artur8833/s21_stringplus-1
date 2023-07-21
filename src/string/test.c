#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include "s21_string.h"

// short atoh(char);
// int atoi(char);
// long atol(char);
// long long atoll(char);
// double stod(char *);
// float stof(char *);
// long double stold(char *);
struct Options{
  int width;
  int length;
  int specifier;
  char *str_form;
};

void *init_var(struct Options, va_list Arg, const char *str);
int s21_sscanf(const char *str, const char *format, ...);

char *func_int(struct Options, va_list Arg, const char *str);



int main() {

  char s1[20];
  char s21_s1[20];
  // float f1, s21_f1;
  int i1 = 0, s21_i1 = 0;

  char *str = "456345zas()&*^*&$&";
  sscanf(str, "%13s", s1);
  s21_sscanf(str, "%d %s", &s21_i1, s21_s1);
  
  return 0;
}

char *func_int(struct Options opt, va_list Arg, const char *str){
	static char mass[256]; // должна быть статик что-бы вернуть указатель на строку
  s21_size_t len_mas = s21_strspn(str, "1234567890");
  s21_memcpy(mass, str, len_mas);
  mass[len_mas] = '\0';
	return mass;
}

int s21_sscanf(const char *str, const char *format, ...) {
  char *s = (char *)str;
  char *f_p = (char *)format;
  va_list Arg;
  va_start(Arg, format);
  struct Options opt = {0};
  while(f_p){
    if (*f_p == '%'){
      f_p++;
      printf("%s\n", str);
      if(isdigit(f_p)){
		    opt.width = *f_p;
        f_p++;
      } else if(*f_p == '*'){
        f_p + 2;
      } else opt.specifier = *f_p;
	  } else f_p++;
    init_var(opt, Arg, s);
    if(*f_p != '\0') f_p++;
  }
  va_end(Arg);
  return 0;
}


void *init_var(struct Options opt, va_list Arg, const char *str) {
  // char c;
  char *s = "234";
  int i = 0;
  while (i == 0) {
    switch (opt.specifier) {
    case 'c': // символ
      // c = (char)va_arg(Arg, int);
      break;
    case 'd': // знаковое десятичное целое число
    i++;
      printf("%s\n", s);
      s = func_int(opt, Arg, str);
      break;
    case 'i': // знаковое целое число (можэт быть десятичным, восьмеричным или
              // шестнадцатиричным)
      break;
    case 'e': // десятичное число с плавающей точкой или научная нотация
              // (мантиса/экспонента)
      break;
    case 'E': // десятичное число с плавающей точкой или научная нотация
              // (мантиса/экспонента)
      break;
    case 'f': // десятичное число с плавающей точкой или научная нотация
              // (мантиса/экспонента)
      break;
    case 'g': // десятичное число с плавающей точкой или научная нотация
              // (мантиса/экспонента)
      break;
    case 'G': // десятичное число с плавающей точкой или научная нотация
              // (мантиса/экспонента)
      break;
    case 'o': // беззнаковое восьмеричное число
      break;
    case 's': // строка символов
      // s = va_arg(Arg, char *);
      break;
    case 'u': // беззнаковое десятичное целое число
      break;
    case 'x': // беззнаковое шестнадцатиричное целое число (любые буквы)
      break;
    case 'X': // беззнаковое шестнадцатиричное целое число (любые буквы)
      break;
    case 'p': // адрес указателя
      break;
    case 'n': // количество символов, считанных до появления %n
      break;
    case '%': // символ %
    }
  }
}




