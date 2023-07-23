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
        if(isdigit(format[i+1]))
        {
            i=parser_nums(str,flags,i,format);
        }
        break;
    case '-':
        flags->alignment=1;
        i++;
        i=parser_nums(str,flags,i,format);
        flags->wight=1;
        break;
    case '.':
        i++;
        i=parser_nums_point(str,flags,i,format);
        //i=parser_nums(str,flags,i,format);
        // printf("format[i]===%c\n", format[i]);   
        flags->precision=1;
        break;
    case ' ':
        i++;
        s21_putchar_to_str(' ', str);
        break;
    default:
        if isdigit (c) // проверяет строку на число
        {   
            // printf("333333333\n");
            flags->wight=1;
            i=parser_nums(str,flags,i,format);
        }
        break;
    }



    return i;
}

int convertNumberToChars(int number, char *str, structs *flags)
{
    char chars[10];
    int index = 0;
    int num_sign=number;
    int precision;
    // printf("flags->sign==%d\n", flags->sign);
    // printf("flags->wight==%d\n", flags->wight);
    printf("num_wight==%d\n", flags->num_wight);
    printf("flags->num_wight2==%d\n", flags->num_wight2);
    // printf("flags->flag_num2==%d\n", flags->flag_num2);
    // // printf("flags->precision==%d\n", flags->precision);
    // printf("flags->num_wight==%d\n", flags->num_wight);
    // // printf("nimberrr==%d\n", number);
    printf("\n");



    if (number == 0)
    {
        s21_putchar_to_str('0', str);
    }

    else
    {
        if ((flags->sign) && (number > 0) && (!flags->wight))
        {
            s21_putchar_to_str('+', str);
        }

        else if (((flags->sign)||(flags->alignment)) && (number < 0) && (!flags->wight))
        {
            number *= -1;
    
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
        else if(number<0){
            number *=-1;
        }
         

        while (number != 0)
        {
            printf("number==%d\n", number);
            int digit = (int)number % 10;
            chars[index++] = digit + '0';
            number /= 10;

        }

        if(num_sign<0)
        {
            flags->num_wight-=1;
        }

        if(((flags->num_wight - flags->num_wight2)>index)&&(flags->flag_num2))
        {
            for(int j=0; j<(flags->num_wight-flags->num_wight2); j++)
            {
                s21_putchar_to_str(' ', str);
            }
        }

        // printf("num_wight==%d\n", flags->num_wight);
        // printf("num_wight2==%d\n", flags->num_wight2);
        // printf("\n");

        if ((flags->wight)&&(!flags->precision)&&(!flags->flag_num2)&&(!flags->sign)){
            if((flags->wight))
            {
                for(int j=index; j<flags->num_wight; j++)
                {   
                    s21_putchar_to_str(' ', str);
                }
            }            
        }
    
        if ((flags->precision))
        {
            // printf("number==%d\n", num_sign);
            // printf("num_wight==%d\n", flags->num_wight);
            // printf("num_wight2==%d\n", flags->num_wight2);
            // printf("flags->wight==%d\n", flags->wight);
            // printf("flags->flags_num2==%d\n", flags->flag_num2);
            // printf("\n");
            
            if ((flags->flag_num2)&&(!flags->num_wight)&&(flags->num_wight2)&&((flags->num_wight-flags->num_wight2)>0))
            {
                precision=flags->num_wight2;
            }
            else if (flags->flag_num2)
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
            //printf("precision==%d\n", precision);
            // printf("\n");
            // printf("iundex==%d\n", index);

            for (int i=0;i<(precision);i++)
            {
                s21_putchar_to_str('0', str);
            }

        }

        if(flags->sign)
        {
            flags->num_wight-=1;
            if((flags->wight))
            {
                for(int j=index; j<flags->num_wight; j++)
                {   
                    s21_putchar_to_str(' ', str);
                }
            }

            if (num_sign>0)
            {
                s21_putchar_to_str('+', str);
            }
            else{
                s21_putchar_to_str('-', str);
            }
            
        }
        

        // printf("flags->flag_num2==%d\n", flags->flag_num2);
        // printf("flags->wight==%d\n", flags->wight);
        // printf("flags->alignment==%d\n", flags->alignment);
        // printf("\n");

        // if ((flags->wight) && (!flags->alignment) && (!flags->flag_num2))
        // {
            
        //     for(int j=index; j<flags->num_wight; j++)
        //     {   
        //         s21_putchar_to_str(' ', str);
        //     }

        // }
        

        if ((num_sign<0) && (!flags->sign) && (flags->wight) &&(!flags->alignment) && (!flags->flag_num2))
        {
            s21_putchar_to_str('-', str);
        }
        

        for (int i = index - 1; i >= 0; i--)
        {
            // printf("chars[i]==%c\n",chars[i]);
            s21_putchar_to_str(chars[i], str);
        }

        
    
        if ((flags->wight) && (flags->alignment))
        {

            if ((flags->precision)&&(precision>0))
            {
                flags->num_wight-=precision;
            }
            // printf("numberddd==%d\n", num_sign);
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

int parser_nums_point( char *str, structs *flags, int i, const char *format)
{
    // printf("flags->wight==%c\n", flags->wight);
    // printf("format[i-1]===%c\n", format[i-1]);
    // printf("format[i]===%c\n", format[i]);
    // printf("format[i+1]===%c\n", format[i+1]);
    // printf("\n");

    int num2;

    flags->flag_num2=1;
    flags->precision=1;


    flags->num_wight2=atoi(&format[i+1]);
    num2=flags->num_wight2;
    // printf("num2==%d\n", num2);
    
    // printf("format[i+1]===%c\n", format[i+1]);
    // printf("try/false===%d\n", isdigit(format[i+1]));
    // printf("\n");

    if (!isdigit(format[i+1]))
    {   
        flags->empty=1;
        // printf("9999\n");
    }


    if ((num2==0)&&(flags->wight) && (!flags->empty)){
        i++;
        // printf("123\n");
    }

    else if ((num2==0)&&(!flags->empty))
    {
        i++;
    }
    
    // else if((num2==0) && (flags->wight) &&(flags->empty))
    // {
    //     i=i;
    // }

    // if((flags->wight) && (flags->empty)){
    //     i=i;
    // }

    for(int j=0;num2>0;j++)
    {
        num2=num2/10;
        i++;
    }

    // if((flags->num_wight2==0) && (!flags->empty))
    // {
    //     i++;
    // }
    
    // printf("format[i]22===%c\n", format[i]);
    // printf("wight=%d\n", flags->wight);
    // printf("num_wight==%d\n", flags->num_wight);
    // printf("num_wight2==%d\n", flags->num_wight2);
    // printf("parsers_num_format[i]===%c\n", format[i]);
    // printf("\n");
    return i;
}

int parser_nums( char *str, structs *flags, int i, const char *format)
{
    // printf("flags->wight==%d\n", flags->wight);
    // printf("format[i-1]===%c\n", format[i-1]);
    // printf("format[i]===%c\n", format[i]);
    // printf("format[i+1]===%c\n", format[i+1]);
    // printf("\n");

    flags->wight=1;
    int num1;
    flags->num_wight=atoi(&format[i+1]);

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
        i++;
        // printf("format[i]11===%c\n", format[i]);
        i=parser_nums_point(str,flags,i,format);
    }
    // printf("num_wight==%d\n", flags->num_wight);
    // printf("format[i]11==%c\n", format[i]);
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
    
    if ((flags->sign) && (number > 0) && (!flags->sign))
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
    int a=69;
    // printf("Test1\n");
    // sprintf(stt, "This is a simple value %d", a);
    // s21_sprintf(str,"This is a simple value %d", a);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    // printf("\n");
   
   
    // printf("Test2\n");
    // int val = 69;
    // sprintf(stt, "%5d", val);
    // s21_sprintf(str,"%5d", val);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    // printf("\n");


    // printf("Test3\n");
    // int val4 = 69;
    // sprintf(stt,"%+12d", val4);
    // s21_sprintf(str,"%+12d",  val4);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    // printf("\n");

    // printf("Test5\n");
    // //(str,"%6.5d Test %.23d Test %3.d TEST %.d %.6d", val10, val11, val12, val13, val14);
    // int val10 = 69;
    // sprintf(stt, "%.0d", val10);
    // s21_sprintf(str,"%.0d", val10);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    // printf("\n");
    
 

    // printf("Test7\n");
    // sprintf(stt, "% d",val10);
    // s21_sprintf(str, "% d",val10);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    // printf("\n");
    
    printf("Test8\n");
    int val24 = -3015;
    int val25 = -712;
    int val26 = -99;
    int val27 = -2939;
    sprintf(stt, "%+d Test %+3.d Test %+5.7d TEST %+10d", val24, val25, val26, val27);
    s21_sprintf(stt, "%+d Test %+3.d Test ", val24, val25);
    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");
    
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
