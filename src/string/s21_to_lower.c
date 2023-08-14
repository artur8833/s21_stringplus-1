#include "../s21_string.h"
//Возвращает копию строки (str), преобразованной в нижний регистр
void *s21_to_lower(const char *str) {
  char *result = S21_NULL;

  if (str) {  // Проверка, что входная строка не является NULL
    s21_size_t len = s21_strlen(str);  // Вычисление длины входной строки
    char *our_str1 = (char *)malloc(
        (len + 1) * sizeof(char));  // Выделение памяти для новой строки
    if (our_str1) {  // Проверка, что память была успешно выделена
      for (s21_size_t i = 0; i <= len;
           i++) {  // Итерация по каждому символу входной строки
        if (str[i] >= 'A' && str[i] <= 'Z') {  // Проверка, является ли симвоk
                                               // символом верхнего регистра
          our_str1[i] =
              str[i] + 'a' - 'A';  // Преобразование символа верхнего регистра в
                                   // символ нижнего регистра
        } else {
          our_str1[i] = str[i];  // Символ не является символом верхнего
                                 // регистра, оставляем его без изменений
        }
      }
      our_str1[len] = '\0';  // Добавление нулевого символа в конец новой строки
      result = our_str1;  // Присвоение указателю result значения новой строки
    }
  }
  return result;
}