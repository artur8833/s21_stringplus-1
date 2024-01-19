#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  structs flags = {0};
  int i = -1;
  str[0] = '\0';
  va_list args;
  va_start(args, format);
  while (format[++i] != '\0') {
    if (format[i] != '%') {
      s21_putchar_to_str(format[i], str);
    }

    else if (format[i] == '%' && format[i + 1]) {
      i = check_flags(format[i + 1], &flags, i, format);
      i = check_size(format[i + 1], &flags, i);
      check_characteristics(format[++i], args, str, &flags);
    }
  }
  va_end(args);
  return s21_strlen(str);
}

int s21_putchar_to_str(const char c, char *str) {
  while (*str != '\0') {
    str++;
  }
  *str = c;
  str++;
  *str = '\0';
  return 1;
}

void check_characteristics(const char c, va_list args, char *str,
                           structs *flags) {
  char ch;
  switch (c) {
    case 'D':
    case 'd':
      write_d(str, flags, args);
      s21_memset(flags, 0, sizeof(structs));
      break;
    case 'C':
    case 'c':
      ch = (char)va_arg(args, int);
      convertCharToString(ch, str, flags);
      s21_memset(flags, 0, sizeof(structs));
      break;
    case 'F':
    case 'f':
      convertfloatToString(str, flags, args);
      s21_memset(flags, 0, sizeof(structs));
      break;
    case 'S':
    case 's':
      convertStringToString(str, flags, args);
      s21_memset(flags, 0, sizeof(structs));
      break;
    case 'U':
    case 'u':
      write_u(str, flags, args);
      s21_memset(flags, 0, sizeof(structs));
      break;
    case '%':
      s21_putchar_to_str('%', str);
      s21_memset(flags, 0, sizeof(structs));
      break;

    default:
      break;
  }
}

void write_u(char *str, structs *flags, va_list args) {
  unsigned long long int arg_u = 0;
  if (flags->flag_h) {
    arg_u = (unsigned long long int)(unsigned short int)va_arg(args, int);
    convertUnsignedToChars(str, flags, arg_u);
  } else if (flags->flag_l) {
    arg_u = (unsigned long long int)va_arg(args, unsigned long int);
    convertUnsignedToChars(str, flags, arg_u);
  } else {
    arg_u = (unsigned long long int)va_arg(args, unsigned int);
    convertUnsignedToChars(str, flags, arg_u);
  }
}

void write_d(char *str, structs *flags, va_list args) {
  if (flags->flag_h) {
    short int arg_d_h = (long long int)(short int)va_arg(args, int);
    convertNumberToChars(str, flags, arg_d_h);
  }

  else if (flags->flag_l) {
    long int arg_d_l = (long long int)va_arg(args, long int);
    convertNumberToChars(str, flags, arg_d_l);
  } else {
    int arg_d = va_arg(args, int);
    convertNumberToChars(str, flags, arg_d);
  }
}

int check_flags(const char c, structs *flags, int i, const char *format) {
  switch (c) {
    case '+':
      flags->sign = 1;
      ++i;
      if (isdigit(format[i + 1])) {
        i = parser_nums(flags, i, format);
      }
      break;
    case '-':
      flags->alignment = 1;
      i++;
      if (format[i + 1] == ' ') {
        i++;
        flags->flag_space = 1;
      } else if (isdigit(format[i + 1])) {
        flags->wight = 1;
        i = parser_nums(flags, i, format);
      }
      break;
    case '.':
      i++;
      i = parser_nums_point(flags, i, format);
      flags->precision = 1;
      break;
    case ' ':
      i++;
      flags->flag_space = 1;

      if (isdigit(format[i + 1])) {
        i = parser_nums(flags, i, format);
        flags->wight = 1;
      } else if (format[i + 1] == '-') {
        flags->alignment = 1;
        i++;
        i = parser_nums(flags, i, format);
      }
      break;
    default:
      if (isdigit(c))  // проверяет строку на число
      {
        flags->wight = 1;
        i = parser_nums(flags, i, format);
      }
      break;
  }

  return i;
}

int check_size(const char c, structs *flags, int i) {
  switch (c) {
    case 'L':
    case 'l':
      flags->flag_l = 1;
      i++;
      break;
    case 'h':
      flags->flag_h = 1;
      i++;
      break;
    default:
      break;
  }
  return i;
}

void convertNumberToChars(char *str, structs *flags, long long number) {
  char chars[700];
  int index = 0;
  int precision;

  if ((flags->flag_space) && (number >= 0)) {
    s21_putchar_to_str(' ', str);
    if ((number == 0) && (!flags->precision)) {
      s21_putchar_to_str('0', str);
    }
  }

  if ((number == 0) && (flags->num_wight) && (flags->wight) &&
      (!flags->flag_space)) {
    chars[0] = '0';
    index = 1;
  } else if ((number == 0) && (!flags->wight) && (!flags->flag_space)) {
    s21_putchar_to_str('0', str);
  }

  if (number < 0) {
    flags->num_wight -= 1;
    number *= -1;
    flags->negative_number = 1;
  }

  if ((flags->negative_number) && (!flags->sign) && (flags->alignment) &&
      (!flags->flag_num2)) {
    s21_putchar_to_str('-', str);
  } else if ((flags->negative_number) && (!flags->wight) && (!flags->sign) &&
             (!flags->alignment)) {
    s21_putchar_to_str('-', str);
  } else if ((flags->negative_number) && (!flags->sign) && (flags->flag_num2) &&
             (flags->wight)) {
    s21_putchar_to_str('-', str);
  }

  while (number != 0) {
    long int digit = (long int)number % 10;
    chars[index++] = digit + '0';
    number /= 10;
  }

  if (((flags->num_wight - flags->num_wight2) > index) && (flags->flag_num2) &&
      (!flags->alignment)) {
    for (int j = 0; j < (flags->num_wight - flags->num_wight2); j++) {
      s21_putchar_to_str(' ', str);
    }
  }

  if ((flags->wight) && (!flags->precision) && (!flags->flag_num2) &&
      (!flags->sign) && (!flags->alignment)) {
    if ((flags->wight)) {
      for (int j = index; j < flags->num_wight; j++) {
        s21_putchar_to_str(' ', str);
      }
    }
  }

  if (flags->sign) {
    if (!flags->negative_number) {
      flags->num_wight -= 1;
    }

    if ((flags->wight) && (!flags->precision)) {
      for (int j = index; j < flags->num_wight; j++) {
        s21_putchar_to_str(' ', str);
      }
    }

    if (!flags->negative_number) {
      s21_putchar_to_str('+', str);
    } else {
      s21_putchar_to_str('-', str);
    }
  }

  if ((flags->precision)) {
    if ((flags->flag_num2) && (!flags->num_wight) && (flags->num_wight2) &&
        ((flags->num_wight - flags->num_wight2) > 0)) {
      precision = flags->num_wight2;
    } else if (flags->flag_num2) {
      precision = (flags->num_wight2 - index);
    } else {
      precision = flags->num_wight - index;
    }

    for (int i = 0; i < (precision); i++) {
      s21_putchar_to_str('0', str);
    }
  }

  if ((flags->negative_number) && (!flags->sign) && (flags->wight) &&
      (!flags->alignment) && (!flags->flag_num2)) {
    s21_putchar_to_str('-', str);
  }

  for (int i = index - 1; i >= 0; i--) {
    s21_putchar_to_str(chars[i], str);
  }

  if ((flags->alignment)) {
    int presAligment;
    if ((flags->flag_num2) && ((flags->num_wight - flags->num_wight2) > 0)) {
      presAligment = flags->num_wight - flags->num_wight2;
    } else if (((flags->flag_num2) &&
                ((flags->num_wight - flags->num_wight2) < 0))) {
      presAligment = 0;
    } else {
      presAligment = flags->num_wight;
    }
    if ((flags->flag_space) && (!flags->negative_number)) {
      presAligment -= 1;
    }
    for (int j = index; j < presAligment; j++) {
      s21_putchar_to_str(' ', str);
    }
  }
}

void convertUnsignedToChars(char *str, structs *flags,
                            unsigned long long number) {
  char chars[700];
  int index = 0;
  int precision;

  if ((number == 0) && (!flags->precision)) {
    s21_putchar_to_str('0', str);
  }

  while (number != 0) {
    long int digit = (long int)number % 10;
    chars[index++] = digit + '0';
    number /= 10;
  }

  if (((flags->num_wight - flags->num_wight2) > index) && (flags->flag_num2) &&
      (!flags->alignment)) {
    for (int j = 0; j < (flags->num_wight - flags->num_wight2); j++) {
      s21_putchar_to_str(' ', str);
    }
  }

  if ((flags->wight) && (!flags->precision) && (!flags->flag_num2) &&
      (!flags->sign) && (!flags->alignment)) {
    if ((flags->wight)) {
      for (int j = index; j < flags->num_wight; j++) {
        s21_putchar_to_str(' ', str);
      }
    }
  }

  if ((flags->precision)) {
    if ((flags->flag_num2) && (!flags->num_wight) && (flags->num_wight2) &&
        ((flags->num_wight - flags->num_wight2) > 0)) {
      precision = flags->num_wight2;
    } else if (flags->flag_num2) {
      precision = (flags->num_wight2 - index);
    } else {
      precision = flags->num_wight - index;
    }

    for (int i = 0; i < (precision); i++) {
      s21_putchar_to_str('0', str);
    }
  }

  if ((flags->negative_number) && (!flags->sign) && (flags->wight) &&
      (!flags->alignment) && (!flags->flag_num2)) {
    s21_putchar_to_str('-', str);
  }

  for (int i = index - 1; i >= 0; i--) {
    s21_putchar_to_str(chars[i], str);
  }

  if (flags->alignment) {
    if ((flags->flag_space) && (!flags->negative_number)) {
      flags->num_wight -= 1;
    }
    for (int j = index; j < flags->num_wight; j++) {
      s21_putchar_to_str(' ', str);
    }
  }
}

int parser_nums_point(structs *flags, int i, const char *format) {
  int num2;

  flags->flag_num2 = 1;
  flags->precision = 1;
  flags->wight = 1;

  flags->num_wight2 = atoi(&format[i + 1]);
  num2 = flags->num_wight2;
  if (!isdigit(format[i + 1])) {
    flags->empty = 1;
  }

  if ((num2 == 0) && (flags->wight) && (!flags->empty)) {
    i++;
  }

  else if ((num2 == 0) && (!flags->empty)) {
    i++;
  }

  for (int j = 0; num2 > 0; j++) {
    num2 = num2 / 10;
    i++;
  }

  return i;
}

int parser_nums(structs *flags, int i, const char *format) {
  flags->wight = 1;
  int num1;
  flags->num_wight = atoi(&format[i + 1]);

  if ((format[i - 1] == '%') && (format[i] == '.') &&
      (format[i + 1] != (isdigit(format[i + 1])))) {
    flags->empty = 1;
  }

  flags->num_wight = atoi(&format[i + 1]);

  if ((flags->num_wight == 0) && (!flags->empty)) {
    i++;
  }

  num1 = flags->num_wight;

  for (int j = 0; num1 > 0; j++) {
    num1 = num1 / 10;
    i++;
  }

  if ((format[i + 1] == '.') && (!flags->empty)) {
    i++;
    i = parser_nums_point(flags, i, format);
  }
  return i;
}

void convertfloatToString(char *str, structs *flags, va_list args) {
  char chars[20];
  int index = 0;
  int index2 = 0;
  int precision;
  long double number = 0;

  if (flags->flag_l) {
    number = (long double)va_arg(args, double);
  } else {
    number = va_arg(args, double);
  }

  if (!flags->precision) {
    precision = 6;
  }

  else if (!flags->flag_num2) {
    precision = flags->num_wight;
  } else {
    precision = flags->num_wight2;
  }

  long long int count =
      countDigits(number, precision);  // считаем количество цифр

  if ((flags->flag_space) && (number >= 0)) {
    s21_putchar_to_str(' ', str);
  }

  if (number < 0) {
    number *= -1;
    count += 1;
    flags->negative_number = 1;
  }

  if ((flags->sign) && (!flags->negative_number) && (!flags->wight)) {
    s21_putchar_to_str('+', str);
  }

  else if ((flags->negative_number) && (!flags->sign) && (flags->alignment) &&
           (!flags->flag_num2)) {
    s21_putchar_to_str('-', str);
  } else if ((flags->negative_number) && (!flags->wight) && (!flags->sign) &&
             (!flags->alignment)) {
    s21_putchar_to_str('-', str);
  } else if ((flags->negative_number) && (!flags->sign) && (flags->flag_num2) &&
             (flags->wight) && (count > flags->num_wight) &&
             (!flags->alignment)) {
    s21_putchar_to_str('-', str);
  } else if ((flags->negative_number) && (!flags->sign) && (flags->flag_num2) &&
             (flags->wight) && (flags->alignment)) {
    s21_putchar_to_str('-', str);
  }

  // Округляем число до нужной точности
  double multiplier = pow(10, precision);
  number = round(number * multiplier) / multiplier;
  long int int_number = (long int)number;

  if (int_number == 0) {
    s21_putchar_to_str('0', str);
  }

  while (int_number != 0) {
    long int digit = int_number % 10;
    chars[index++] = digit + '0';
    int_number /= 10;
  }

  // printf("count==%lld\n", count);

  if ((flags->num_wight > count) && (flags->flag_num2) && (!flags->alignment)) {
    for (int j = count; j < flags->num_wight; j++) {
      s21_putchar_to_str(' ', str);
    }
    if ((flags->negative_number) && (flags->num_wight > count) &&
        (!flags->sign)) {
      s21_putchar_to_str('-', str);
    }
  }

  if ((flags->wight) && (!flags->precision) && (!flags->flag_num2) &&
      (!flags->sign) && (!flags->alignment)) {
    if ((flags->wight)) {
      for (int j = index + precision + 1; j < flags->num_wight; j++) {
        s21_putchar_to_str(' ', str);
      }
    }
  }

  if (flags->sign) {
    if (!flags->negative_number) {
      flags->num_wight -= 1;
    }

    if ((flags->wight) && (!flags->precision)) {
      for (int j = index; j < flags->num_wight; j++) {
        s21_putchar_to_str(' ', str);
      }
    }

    if (!flags->negative_number) {
      s21_putchar_to_str('+', str);
    } else {
      s21_putchar_to_str('-', str);
    }
  }

  if ((flags->negative_number) && (!flags->sign) && (flags->wight) &&
      (!flags->alignment) && (!flags->flag_num2)) {
    s21_putchar_to_str('-', str);
  }

  for (int i = index - 1; i >= 0; i--) {
    s21_putchar_to_str(chars[i], str);
  }

  if (precision > 0) {  // Если точность больше нуля, добавляем десятичную часть
    // Вычисляем дробную часть числа
    long double fractionalPart =
        number -
        (long long int)number;  // Умножаем дробную часть на 10^precision, чтобы
                                // перевести ее в целое число
    long long int fractionalInteger =
        round(fractionalPart * pow(10, precision));

    s21_putchar_to_str('.', str);  // Добавляем разделитель десятичной части и
                                   // переводим его в строку
    int count_fractionalInteger = countDigits(fractionalInteger, precision);
    if (fractionalInteger == 0) {
      for (int i = 0; i < precision; i++) {
        s21_putchar_to_str('0', str);
      }
    }

    else if (count_fractionalInteger < precision) {
      for (int i = count_fractionalInteger; i < precision; i++) {
        s21_putchar_to_str('0', str);
      }
    }

    while (fractionalInteger != 0) {
      long long int digit = fractionalInteger % 10;
      chars[index2++] = digit + '0';
      fractionalInteger /= 10;
    }

    for (int i = index2 - 1; i >= 0; i--) {
      s21_putchar_to_str(chars[i], str);
    }
  }

  if (flags->alignment) {
    if ((flags->flag_space) && (!flags->negative_number)) {
      flags->num_wight -= 1;
    }
    for (int j = count; j < flags->num_wight; j++) {
      s21_putchar_to_str(' ', str);
    }
  }
}

int countDigits(long double num, int precision) {
  int count = 0;
  long long int integerPart = (long long int)num;  // Получаем целую часть числа
  // Подсчитываем количество цифр в целой части+
  if (integerPart == 0) {
    count = 1;  // Если число равно нулю, то у него одна цифра
  } else {
    while (integerPart != 0) {
      count++;
      integerPart /= 10;
    }
  }
  // Подсчитываем количество цифр в дробной части
  if (precision > 0) {
    long double fractionalPart = num - (long long int)num;
    long long int fractionalInteger =
        round(fractionalPart * pow(10, precision));

    if (fractionalInteger) {
      count += 1;
    }

    while (fractionalInteger != 0) {
      count++;
      fractionalInteger /= 10;
    }
  }

  return count;
}

void convertStringToString(char *str, structs *flags, va_list args) {
  char *s = va_arg(args, char *);
  int len = s21_strlen(s);
  int precision;
  if ((flags->wight) && (!flags->alignment)) {
    for (int j = len; j < flags->num_wight; j++) {
      s21_putchar_to_str(' ', str);
    }
  }

  if ((flags->precision)) {
    if ((flags->flag_num2) && ((flags->num_wight - flags->num_wight2) > 0)) {
      precision = flags->num_wight - flags->num_wight2;
    } else if (!flags->flag_num2) {
      precision = flags->num_wight;
    } else {
      precision = flags->num_wight - len;
    }

    if ((!flags->alignment) && ((flags->num_wight - flags->num_wight2) > 0)) {
      for (int i = 0; i < (precision); i++) {
        s21_putchar_to_str(' ', str);
      }
    }
  }

  if ((!flags->flag_num2) && (flags->wight) && (flags->precision)) {
    for (int i = 0; i < flags->num_wight; i++) {
      s21_putchar_to_str(s[i], str);
    }
  } else if ((flags->flag_num2) && (len > flags->num_wight2)) {
    for (int i = 0; i < flags->num_wight2; i++) {
      s21_putchar_to_str(s[i], str);
    }

  } else if (((flags->flag_num2) && (len < flags->num_wight2))) {
    for (int i = 0; i < len; i++) {
      s21_putchar_to_str(s[i], str);
    }
  } else if (!flags->precision) {
    for (int i = 0; i < len; i++) {
      s21_putchar_to_str(s[i], str);
    }
  }

  if ((flags->alignment)) {
    if (!flags->flag_num2) {
      for (int j = len; j < flags->num_wight; j++) {
        s21_putchar_to_str(' ', str);
      }

    } else if ((flags->flag_num2)) {
      for (int j = 0; j < precision; j++) {
        s21_putchar_to_str(' ', str);
      }
    }
  }
}

void convertCharToString(char c, char *str, structs *flags) {
  int precision;
  if ((flags->precision)) {
    precision = flags->num_wight;

    if ((!flags->alignment) && ((flags->num_wight - flags->num_wight2) > 0)) {
      for (int i = 0; i < precision; i++) {
        s21_putchar_to_str(' ', str);
      }
    }
  }

  if ((flags->wight) && (!flags->flag_num2) && (!flags->alignment)) {
    for (int i = 1; i < flags->num_wight; i++) {
      s21_putchar_to_str(' ', str);
    }
  }

  s21_putchar_to_str(c, str);
  if ((flags->alignment)) {
    if (!flags->flag_num2) {
      for (int j = 1; j < flags->num_wight; j++) {
        s21_putchar_to_str(' ', str);
      }

    } else if (flags->flag_num2) {
      for (int j = 1; j < precision; j++) {
        s21_putchar_to_str(' ', str);
      }
    }
  }
}
