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
            i = check_flags(format[i+1], str, &flags, i, format);
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
    case 'D':
    case 'd':
        d = va_arg(args, int);
        convertNumberToChars(d, str, flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'C':
    case 'c':
        ch = (char)va_arg(args, int);
        convertCharToString(ch,str,flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'F':
    case 'f':
        f = va_arg(args, double);
        convertfloatToString(f, str, flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'S':
    case 's':
        char* s = va_arg(args, char *);
        convertStringToString(s, str,flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'U':
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
    switch (c)
    {
    case '+':
        flags->sign = 1;
        ++i;
        break;
    case '-':
        flags->alignment=1;
        i++;
        i=parser_nums(str,flags,i,format);
        flags->wight=1;
        break;
    case '.':
        i++;
        i=parser_nums(str,flags,i,format);     
        flags->precision=1;
        break;
    default:
        break;
    }

    if isdigit (c) // проверяет строку на число
    {   
        i=parser_nums(str,flags,i,format);
        flags->wight=1;             
    }


    return i;
}

int convertNumberToChars(int number, char *str, structs *flags)
{
    char chars[10];
    int index = 0;
    int num_sign=number;
    int precision;
    // printf("flags->num_wight==%d\n", flags->num_wight);
    // printf("nimberrr==%d\n", number);
    // printf("\n");
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

        else if (((flags->sign)||(flags->alignment)) && (number < 0))

        {
            number *= -1;
            s21_putchar_to_str('-', str);
        }

        else if ((number < 0) && (!flags->sign) && (!flags->wight))

        {
            number *= -1;
            s21_putchar_to_str('-', str);
        }
        else if((number<0) && (!flags->sign) && (flags->flag_num2) && (flags->wight)){
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

        //printf("presicion==%d\n", flags->precision);

        if ((flags->wight) && (!flags->alignment) && (flags->flag_num2) )
        {
            if (num_sign<0)
            {
                flags->num_wight-=1;
            } 
            
            if((flags->num_wight-flags->num_wight2)>index)
            {
                for(int j=0; j<(flags->num_wight-flags->num_wight2); j++)
                {
                    s21_putchar_to_str(' ', str);
                }
            }

        }

        // printf("num_wight==%d\n", flags->num_wight);
        // printf("num_wight2==%d\n", flags->num_wight2);
        // printf("\n");
    
        if ((flags->precision))
        {
            // printf("number==%d\n", num_sign);
            // printf("num_wight==%d\n", flags->num_wight);
            // printf("num_wight2==%d\n", flags->num_wight2);
            // printf("flags->wight==%d\n", flags->wight);
            // printf("flags->flags_num2==%d\n", flags->flag_num2);
            // printf("\n");
            
            if ((flags->flag_num2)&&(!flags->num_wight)&&(!flags->num_wight2))
            {

                //printf("donerrrrrr\n");
                precision=flags->num_wight2;
            }
            else if ((flags->flag_num2) && (flags->wight))
            {
                // printf("2222\n");
                precision=(flags->num_wight2-index);
            }
            else
            {
                //printf("donerrrrr2222222r\n");
                precision=flags->num_wight-index;
            }
            // printf("number==%d\n", num_sign);
            // printf("precision==%d\n", precision);
            // printf("\n");
            // printf("iundex==%d\n", index);

            for (int i=0;i<(precision);i++)
            {
                s21_putchar_to_str('0', str);
            }
        }
        


        if ((flags->wight) && (!flags->alignment) && (!flags->flag_num2))
        {
            if (num_sign<0)
            {
                flags->num_wight-=1;
            } 
            for(int j=index; j<flags->num_wight; j++){
                s21_putchar_to_str(' ', str);
            }
        }
        


        if ((num_sign<0) && (!flags->sign) && (flags->wight) &&(!flags->alignment) && (!flags->flag_num2))
        {
            s21_putchar_to_str('-', str);
        }
        
        for (int i = index - 1; i >= 0; i--)
        {
            s21_putchar_to_str(chars[i], str);
        }

        
    
        if ((flags->wight) && (flags->alignment))
        {
            if(num_sign<0)
            {
                flags->num_wight-=1;
            }
            
            if ((flags->precision)&&(precision>0))
            {
                flags->num_wight-=precision;
            }
            // printf("number==%d\n", num_sign);
            // printf("presicion==%d\n", precision);
            // printf("flags->num_wight==%d\n", flags->num_wight);
            // printf("\n");

            for(int j=index; j<flags->num_wight; j++)
            {
                s21_putchar_to_str(' ', str);
            }
        }

    }
    
    return index;
}


int parser_nums( char *str, structs *flags, int i, const char *format)
{
    int num1;
    int num2;
    // printf("format[i-1]===%c\n", format[i-1]);
    // printf("format[i]===%c\n", format[i]);
    // printf("format[i+1]===%c\n", format[i+1]);
    // printf("\n");

    if((format[i-1]=='%')&&(format[i]=='.')&&(format[i+1]!=(isdigit(format[i+1]))))
    {
        flags->empty=1;
    }

    flags->num_wight=atoi(&format[i+1]);
    
    if((flags->num_wight==0) && (!flags->empty))
    {
        i++;
    }
    
    num1=flags->num_wight;

    for(int j=0;num1>0;j++)
    {
        num1=num1/10;
        i++;
    }
    

    if((format[i+1]=='.') && (!flags->empty))
    {

        flags->precision=1;
        i++;
        
        flags->num_wight2=atoi(&format[i+1]);

        if((flags->num_wight2==0))
        {
            flags->flag_num2=1;
        }

        num2=flags->num_wight2;
        for(int j=0;num2>0;j++)
        {
            num2=num2/10;
            i++;
            flags->flag_num2=1;
        }

    }
    
    // printf("num_wight==%d\n", flags->num_wight);
    //printf("format[i]22==%c\n", format[i]);
    return i;

}


void convertfloatToString(double number, char *str, structs *flags)
{
    char chars[20];
    int index = 0;
    int index2=0;
    int num_sign=number;
    int precision;
    if(!flags->precision)
    {
        precision=6;
    }
    else{
    
        precision=flags->num_wight;
        
    }
    
    int count=countDigits(number,precision);
    //printf("count==%d\n", count);
    
    if ((flags->sign) && (number > 0))
    {
        s21_putchar_to_str('+', str);
    }
    
    else if (((flags->sign)||(flags->alignment)) && (number < 0))
    {
        number *= -1;
        
        s21_putchar_to_str('-', str);
    }
    
    else if ((number < 0) && (!flags->sign) && (!flags->wight))
    {
        number *= -1;
        s21_putchar_to_str('-', str);
    }
    
    if ((flags->wight) && (!flags->alignment))
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
        //printf("fractionalInteger==%ld\n", fractionalInteger);
        // Добавляем разделитель десятичной части и переводим его в строку
        
        s21_putchar_to_str('.', str);
        while (fractionalInteger != 0)
        {
            int digit = fractionalInteger % 10;
            chars[index2++] = digit + '0';
            fractionalInteger /= 10;
        }
        
        //printf("pres==%d\n", flags->precision);
        
        if (fractionalInteger==0)
        {
            for(int j=0; j<flags->num_wight; j++)
            {
                s21_putchar_to_str('0', str);
            }
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
    
    if ((flags->wight) && (!flags->alignment))
    {
        for(int j=len; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }    


    if ((flags->precision))
    {
        for (int i = 0; i < flags->num_wight; i++)
        {
            s21_putchar_to_str(s[i], str);
        }        
    }

    else
    {
        for (int i = 0; i < len; i++)
        {
            s21_putchar_to_str(s[i], str);
        }
    
    }

    if ((flags->wight) && (flags->alignment))
    {
        for(int j=len; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }        
    }

}

void convertCharToString(char c,char *str,structs *flags)
{

    if ((flags->wight) && (!flags->alignment))
    {
        for(int j=1; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }    

    s21_putchar_to_str(c, str);

    if ((flags->wight) && (flags->alignment))
    {
        printf("Donen\n");
        for(int j=1; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }        
}

int main()
{
    char str[1250];
    char stt[500];
    char ss[50] = "End strok";
    int a=-12;
    printf("Test1\n");
    sprintf(stt, "Test %d Test", a);
    s21_sprintf(str,"Test %d Test", a);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");
   
   
    printf("Test2\n");
    int val = 012;
    int val2 = -017;
    int val3 = 07464;
    sprintf(stt, "%d Test %d Test %d", val, val2, val3);
    s21_sprintf(str,"%d Test %d Test %d", val, val2, val3);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");


    printf("Test3\n");
    int val4 = 3015;
    int val5 = 712;
    int val6 = 99;
    sprintf(stt, "%d Test %d Test %d", val4, val5, val6);
    s21_sprintf(str,"%d Test %d Test %d",  val4, val5, val6);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");

    printf("Test4\n");
    int val7 = -3015;
    int val8 = -11234;
    int val9 = -99;
    sprintf(stt, "%3d Test %5d Test %10d", val7, val8, val9);
    s21_sprintf(str,"%3d Test %5d Test %10d", val7, val8, val9);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");
   
    printf("Test5\n");
    int val10 = -3015;
    int val11 = -712;
    int val12 = -99;
    int val13 = -38;
    int val14 = -100;
    sprintf(stt, "%6.5d Test %.23d Test %3.d TEST %.d %.6d", val10, val11, val12, val13, val14);
    s21_sprintf(str,"%6.5d Test %.23d Test %3.d TEST %.d %.6d", val10, val11, val12, val13, val14);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");
    
 

    printf("Test7\n");
    int val19 = -3015;
    int val20 = -712;
    int val21 = -99;
    int val22 = -2939;
    int val23 = -0123;
    sprintf(stt, "%0d Test %0.d Test %0.0d TEST %0d GOD %.d", val19, val20, val21, val22, val23);
    s21_sprintf(str,"Test %0.0d TEST %0d GOD %.d", val21, val22, val23);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");
    
    // printf("Test8\n");
    // int val24 = -3015;
    // int val25 = -712;
    // int val26 = -99;
    // int val27 = -2939;
    // sprintf(stt, "%+d Test %+3.d Test %+5.7d TEST %+10d", val24, val25, val26, val27);
    // s21_sprintf(str,"%+d Test %+3.d Test %+5.7d TEST %+10d", val24, val25, val26, val27);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    // printf("\n");
    
    // printf("Test9\n");
    // int val28 = -32;
    // int val29 = -8899;
    // int val30 = -91918;
    // int val31 = -32311;
    // int val32 = -23;
    // sprintf(stt, "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d", val28, val29, val30, val31, val32);
    // s21_sprintf(str,"% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d", val28, val29, val30, val31, val32);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    
    // printf("Test10\n");
    // int val33 = -3231;
    // int val34 = -3231;
    // int val35 = 3231;
    // int val36 = 3231;
    // sprintf(stt, "%- d Test %- 15d sdasda %- 15d sdsad %- d", val33, val34, val35, val36);
    // s21_sprintf(str,"%- d Test %- 15d sdasda %- 15d sdsad %- d", val33, val34, val35, val36);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);


    return 0;
}
