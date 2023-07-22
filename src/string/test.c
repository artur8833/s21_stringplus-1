# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
#include <string.h>

int main()
{
    char chars[10];
    int index = 0; 
    float number=20;
    int int_number;
    int precision;

    int_number=(int)number;
    //printf("%d\n",int_number);
    if (int_number == 0) {
        chars[index++] = '0'; 
    } 
    else
    {
        while (int_number != 0) {
            int digit = int_number % 10;
            printf("d=%d\n", digit);
            chars[index++] = digit + '0';
            int_number /= 10;
        }
            
        for (int i = index - 1; i >= 0; i--) {
            printf("%c",chars[i]);
        }
        
        if (number==(float)number)
        {
            memset(chars,0,10);
            index=0;
            putchar('.',str);
            float temp_float=number-int_number;
            for(int i=0;i<precision;i++){
                temp_float*=10;
                int (PlusNum)=(int)temp_float;
                chars[index++]='0' + PlusNum;
                temp_float-=PlusNum;
                
            }
        }
    }
}


void floatToString(float num, char* str, int precision) {
    int integerPart = (int)num;  // Получаем целую часть числа
    
    // Преобразуем целую часть в символы и сохраняем в строку
    sprintf(str, "%d", integerPart);
    
    int len = strlen(str);  // Получаем длину строки
    
    if (precision > 0) {
        str[len++] = '.';  // Добавляем точку в строку 
        float fractionalPart = num - integerPart;  // Получаем дробную часть числа
        // Умножаем дробную часть на 10^precision, чтобы получить нужное количество знаков после запятой
        for (int i = 0; i < precision; i++) {
            fractionalPart *= 10;
            int digit = (int)fractionalPart;  // Получаем очередную цифру после запятой
            str[len++] = '0' + digit;  // Преобразуем цифру в символ и добавляем в строку
            fractionalPart -= digit;  // Исключаем уже добавленную цифру из дробной части
        }
    }
    
    str[len] = '\0';  // Добавляем завершающий нулевой символ
}