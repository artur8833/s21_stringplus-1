#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...)
{
    structs flags = {0};
    int result;
    result = 0;
    int i = -1;
    str[0] = '\0';
    va_list args;
    va_start(args, format);
    while (format[++i] != '\0')
    {
        if (format[i] != '%')
        {
            result += s21_putchar_to_str(format[i], str);
        }

        else if (format[i] == '%' && format[i + 1])
        {
            i = check_flags(format[i + 1], str, &flags, i, format);
            check_characteristics(format[++i], args, str, &flags);
        }
        
    }
    va_end(args);
    return result;
}

int s21_putchar_to_str(const char c, char *str)
{
    while (*str != '\0')
    {
        str++;
    }
    *str = c;
    str++;
    *str = '\0';
    return 1;
}

int check_characteristics(const char c, va_list args, char *str, structs *flags)
{
    unsigned int u;
    int d;
    float f;
    char ch;
    switch (c)
    {
    case 'd':
        d = va_arg(args, int);
        convertNumberToChars(d, str, flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'c':
        ch = (char)va_arg(args, int);
        convertCharToString(ch,str,flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'f':
        f = va_arg(args, double);
        flags->float_flag=1;
        convertfloatToString(f, str, 6, flags);
        memset(flags,0,sizeof(structs));
        break;
    case 's':
        char* s = va_arg(args, char *);
        convertStringToString(s, str,flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'u':
        u = va_arg(args, unsigned int);
        convertNumberToChars(u, str, flags);
        memset(flags,0,sizeof(structs));
        break;
    case '%':
        s21_putchar_to_str('%', str);
        memset(flags,0,sizeof(structs));
        break;

    default:
        break;
    }

    return 0;
}

int check_flags(const char c, char *str, structs *flags, int i, const char *format)
{
     
    if isdigit (c) // проверяет строку на число
    {
        flags->wight=1;
        i=file_wight(str,flags,i,format);       
    }

    switch (c)
    {
    case '+':
        flags->sign = 1;
        ++i;
        break;
    case '-':
        flags->alignment=1;
    default:
        break;
    }
    return i;
}

int convertNumberToChars(int number, char *str, structs *flags)
{
    char chars[10];
    int index = 0;
    int num_sign=number;

    if (number == 0)
    {
        s21_putchar_to_str('0', str);
    }

    else
    {
        if ((flags->sign) && (number > 0))
        {
            s21_putchar_to_str('+', str);
        }

        else if ((flags->sign) && (number < 0))
        {
            number *= -1;
            s21_putchar_to_str('-', str);
        }


        else if ((number < 0) && (!flags->sign) && (!flags->wight))
        {
            number *= -1;
            s21_putchar_to_str('-', str);
        }

        else if((number < 0) && (!flags->sign) && (flags->wight))
        {
            number *= -1;
        }
         
        while (number != 0)
        {
            int digit = (int)number % 10;
            chars[index++] = digit + '0';
            number /= 10;
        }

        if ((flags->wight))
        {
            if (num_sign<0)
            {
                flags->num_wight-=1;
            } 

            for(int j=index; j<flags->num_wight; j++){
                s21_putchar_to_str(' ', str);
            }
        }

        printf("wight===%d\n", flags->wight);
        if ((num_sign<0) && (!flags->sign) && (flags->wight))
        {
            s21_putchar_to_str('-', str);
        }

        for (int i = index - 1; i >= 0; i--)
        {
            s21_putchar_to_str(chars[i], str);
        }
    }
    
    return index;
}


int file_wight( char *str, structs *flags, int i, const char *format)
{
   
    flags->num_wight=atoi(&format[i+1]);
    int num2;
    num2=flags->num_wight;
    for(int j=0;num2>0;j++)
    {
        num2=num2/10;
        i++;
    }
    return i;
}


void convertfloatToString(double number, char *str, int precision, structs *flags)
{
    char chars[20];
    int index = 0;
    int index2=0;
    int num_sign=number;

    int count=countDigits(number,precision);
    
    if ((flags->sign) && (number > 0))
    {
        s21_putchar_to_str('+', str);
    }
    
    else if ((flags->sign) && (number < 0))
    {
        number *= -1;
        
        s21_putchar_to_str('-', str);
    }
    
    else if ((number < 0) && (!flags->sign) && (!flags->wight))
    {
        number *= -1;
        s21_putchar_to_str('-', str);
    }
    

    if ((flags->wight))
    {
        if (number<0)
        {
            count++;
        }
        for(int j=count; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }
    
    if((number < 0) && (!flags->sign) && (flags->wight))
    {
        number *= -1;
        s21_putchar_to_str('-', str);
    }
    // Округляем число до нужной точности
    double multiplier = pow(10, precision);
    number = round(number * multiplier) / multiplier;

    int int_number=(int)number;
    
    while (int_number != 0)
    {
        int digit = int_number % 10;
        chars[index++] = digit + '0';
        int_number /= 10;
    }

    for (int i = index - 1; i >= 0; i--)
    {
        s21_putchar_to_str(chars[i], str);
    }    
    
    // Если точность больше нуля, добавляем десятичную часть
    if (precision > 0) {
        // Вычисляем дробную часть числа
        double fractionalPart = number - (int)number;
        // Умножаем дробную часть на 10^precision, чтобы перевести ее в целое число
        long fractionalInteger = round(fractionalPart * pow(10, precision));
        // Добавляем разделитель десятичной части и переводим его в строку
        s21_putchar_to_str('.', str);

        while (fractionalInteger != 0)
        {
            int digit = fractionalInteger % 10;
            chars[index2++] = digit + '0';
            fractionalInteger /= 10;
        }
    
        for (int i = index2 - 1; i >= 0; i--)
        {
            s21_putchar_to_str(chars[i], str);
        }

    }

}

int countDigits(float num, int precision) {
    int count = 0;
    int integerPart = (int)num; // Получаем целую часть числа
    // Подсчитываем количество цифр в целой части+
    if (integerPart == 0) {
        count = 1; // Если число равно нулю, то у него одна цифра
    } 
    else {
        while (integerPart != 0) {
            count++;
            integerPart /= 10;
        }
    }
    // Подсчитываем количество цифр в дробной части
    float fractionalPart = num - (int)num;
    long fractionalInteger = round(fractionalPart * pow(10, precision));
    if(fractionalInteger){
        count+=1;
    }
    while (fractionalInteger != 0) {
        count++;
        int digit = fractionalInteger % 10;
        fractionalInteger /= 10;
    }

    return count;
}

double roundToDec(double num, int dec)
{
    double multi = pow(10, dec);
    double rounded = (round(num * multi)) / multi;
    return rounded;
}

void convertStringToString(char *s, char *str,structs *flags)
{
    int len = strlen(s);
    if ((flags->wight))
    {
        for(int j=len; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }    

    for (int i = 0; i < len; i++)
    {
        s21_putchar_to_str(s[i], str);
    }

}

void convertCharToString(char c,char *str,structs *flags)
{
    if ((flags->wight))
    {
        for(int j=1; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }    

    s21_putchar_to_str(c, str);
}

int main()
{
    char str[1250];
    char stt[500];
    char ss[50] = "End strok";
    int age = 5;
    unsigned int u = 54546456;
    int a = 1233;
    float b = -12.11231;
    unsigned int money = -1;
    char chh='d';


    sprintf(stt, "'Test float=%14f, test int=%6d, test str=%12s, test char=%3c, test_proc=%%'\n", b,a,ss, chh);
    s21_sprintf(str,"'Test float=%14f, test int=%6d, test str=%12s, test char=%3c, test_proc=%%'\n", b,a,ss, chh);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    return 0;
}
