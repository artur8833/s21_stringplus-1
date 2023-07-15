#include <stdio.h>

int countDigits(float num) {
    int count = 0;
    int integerPart = (int)num; // Получаем целую часть числа

    // Подсчитываем количество цифр в целой части
    if (integerPart == 0) {
        count = 1; // Если число равно нулю, то у него одна цифра
    } else {
        while (integerPart != 0) {
            count++;
            integerPart /= 10;
        }
    }

    // Подсчитываем количество цифр в дробной части
    float fractionalPart = num - integerPart;
    while (fractionalPart != 0) {
        count++;
        fractionalPart *= 10;
        fractionalPart -= (int)fractionalPart;
    }

    return count;
}

int main() {
    float number = 123.45;
    int digitCount = countDigits(number);
    printf("Количество цифр: %d\n", digitCount);

    return 0;
}