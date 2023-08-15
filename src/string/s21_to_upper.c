#include "../s21_string.h"
//Возвращает копию строки (str), преобразованной в верхний регистр
void *s21_to_upper(const char *str) {
  char *result = S21_NULL;

  if (str) {  // Проверка, что входная строка не является NULL
    s21_size_t len = s21_strlen(str);  // Вычисление длины входной строки
    char *our_str1 = (char *)malloc(
        (len + 1) * sizeof(char));  // Выделение памяти для новой строки
    if (our_str1) {  // Проверка, что память была успешно выделена
      for (s21_size_t i = 0; i <= len;
           i++) {  // Итерация по каждому символу входной строки
        if (str[i] >= 'a' &&
            str[i] <= 'z') {  // Проверка, является ли символ строчной буквой
          our_str1[i] = str[i] - 'a' +
                        'A';  // Преобразование строчной буквы в верхний регистр
        } else {
          our_str1[i] = str[i];  // Символ не является строчной буквой,
                                 // оставляем его без изменений
        }
      }
      our_str1[len] = '\0';  // Добавление нулевого символа в конец новой строки
      result = our_str1;  // Присвоение указателю result значения новой строки
    }
  }
  return result;
}