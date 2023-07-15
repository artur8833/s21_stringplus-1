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
    while (*str)
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
    char ch, *s;
    switch (c)
    {
    case 'd':
        d = va_arg(args, int);
        convertNumberToChars(d, str, flags);
        break;
    case 'c':
        ch = (char)va_arg(args, int);
        s21_putchar_to_str(c, str);
        break;
    case 'f':
        f = va_arg(args, double);
        flags->float_flag=1;
        convertfloatToString(f, str, 0, flags);
        break;
    case 's':
        s = va_arg(args, char *);
        convertStringToString(s, str);
        break;
    case 'u':
        u = va_arg(args, unsigned int);
        convertNumberToChars(u, str, flags);
        break;
    case '%':
        s21_putchar_to_str('%', str);
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
        //printf("1i===%d\n", i);
       
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
        
        //printf("number==%d\n", number);
 
        while (number != 0)
        {
            int digit = (int)number % 10;
            chars[index++] = digit + '0';
            number /= 10;
        }

        if ((flags->wight)&&(!flags->float_flag))
        {
            //printf("num_wight==%d\n", flags->num_wight);
            if (num_sign<0)
            {
                flags->num_wight-=1;
            } 

            for(int j=index; j<flags->num_wight; j++){
                s21_putchar_to_str(' ', str);
            }
        }

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
    // printf("2i===%d\n", i);
    // printf("format[i]===%c\n", format[i]);
    // printf("numbers===%d\n", numbers);
    int num2;
    num2=flags->num_wight;
    for(int j=0;num2>0;j++)
    {
        num2=num2/10;
        i++;
    }
    // printf("3i===%d\n", i);
    return i;
}


void convertfloatToString(double number, char *str, int precision, structs *flags)
{
    char chars[20];
    int index = 0;
    int wight;
    int int_number = (int)number;
    wight=convertNumberToChars(int_number, str, flags);
    s21_putchar_to_str('.', str);
    long double temp_float = number - int_number;
    temp_float = roundToDec(temp_float, 50);
    for (int i = 0; i < 6; i++)
    {
        temp_float *= 10;
        int PlusNum = (int)temp_float;
        chars[index++] = PlusNum + '0';
        temp_float -= PlusNum;
    }
    for (int i = 0; i < index; i++)
    {
        s21_putchar_to_str(chars[i], str);
    }

}



double roundToDec(double num, int dec)
{
    double multi = pow(10, dec);
    double rounded = (round(num * multi)) / multi;
    return rounded;
}

void convertStringToString(char *s, char *str)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        s21_putchar_to_str(s[i], str);
    }
}

int main()
{
    char str[1250];
    char stt[500];
    char ss[50] = "End strok";
    int age = 5;
    unsigned int u = 54546456;
    int a = 1233;
    float b = 12.11;
    double money = 20.3;

    sprintf(stt, "'%12f'\n", b);
    s21_sprintf(str, "'%12f'\n", b);
    printf("origin == %s\n", stt);
    printf("my func == %s\n", str);
    return 0;
}