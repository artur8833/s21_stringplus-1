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

            i = check_size(format[i+1], str, &flags, i, format);
            // printf("wight==%d\n", flags.wight);
            check_characteristics(format[++i], args, str, &flags);
        }
        
    }
    va_end(args);

    // printf("str in func == %s\n", str);
    // printf("size in func ==%ld\n", strlen(str));
    // printf("\n");
    return strlen(str);
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
    // printf("size==%ld\n", strlen(str));

    return 1;
}

int check_characteristics(const char c, va_list args, char *str, structs *flags)
{
    char ch;
    switch (c)
    {
    case 'D':
    case 'd':
        convertNumberToChars(str, flags, args);
        memset(flags,0,sizeof(structs));
        break;
    case 'C':
    case 'c':
        ch = (char)va_arg(args, int);
        // printf("123'n");
        convertCharToString(ch,str,flags);
        memset(flags,0,sizeof(structs));
        break;
    case 'F':
    case 'f':
        convertfloatToString(str, flags, args);
        memset(flags,0,sizeof(structs));
        break;
    case 'S':
    case 's':
        convertStringToString(str, flags, args);
        memset(flags,0,sizeof(structs));
        break;
    case 'U':
    case 'u':
        convertNumberToChars(str, flags, args);
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
        if (format[i+1]==' ')
        {
            i++;
            flags->flag_space=1;
        }
        // else if(format[i+1]=='.')
        // {
        //     i++;
        //     i=parser_nums_point(str,flags,i,format);
        //     flags->precision=1;
        // }
        else if(isdigit(format[i+1]))
        {   
            flags->wight=1;
            i=parser_nums(str,flags,i,format);
        }
        break;
    case '.':
        i++;
        i=parser_nums_point(str,flags,i,format);
        flags->precision=1;
        break;
    case ' ':
        i++;
        flags->flag_space=1;
        if(isdigit(format[i+1]))
        {
            i=parser_nums(str,flags,i,format);
            flags->wight=1;

        }
        else if(format[i+1]=='-'){
            flags->alignment=1;
            i++;
            i=parser_nums(str,flags,i,format);
            // printf("wight==%d\n", flags->num_wight);
        }
        break;
    default:
        if (isdigit (c)) // проверяет строку на число
        {   
            flags->wight=1;
            i=parser_nums(str,flags,i,format);
        }
        break;
    }

    return i;
}

int check_size(const char c, char *str, structs *flags,int i,const char *format){

    // printf("format[i-1]===%c\n", format[i-1]);
    // printf("format[i]===%c\n", format[i]);
    // printf("format[i+1]===%c\n", format[i+1]);
    // printf("c===%c\n", c);
    // printf("\n");   

    switch (c)
    {
    case 'L':
    case 'l':
        flags->flag_l=1;
        i++;
        break;
    case 'h':
        flags->flag_h=1;
        i++;
    break;
    default:
        break;
    }
    return i;
}

int converFarmat( long double number, structs *flags)
{    
    if(flags->flag_l){
        number = (long int) number;
    }
    else if(flags->flag_h){
        number = (short int) number;
    }

    return number;
}


int convertNumberToChars(char *str, structs *flags, va_list args)
{
    //uns igned int u = va_arg(args, unsigned int);
    long int number=va_arg(args,long int);
    char chars[700];
    int index = 0;
    int num_sign=number;
    int precision;
    
    if(flags->flag_l){
        number = (long int) number;
    }
    else if(flags->flag_h){
        number = (short int) number;
        num_sign=(short int) number;
    }
    else{
        number=(int) number;
    }

    // printf("number==%ld\n", number);
    // printf("num_sign==%ld\n", num_sign);
    // printf("flags->sign==%d\n", flags->sign);
    // printf("flags->wight==%d\n", flags->wight);
    // printf("flags->space==%d\n", flags->flag_space);
    // printf("flags->aligment==%d\n", flags->alignment);
    // printf("num_wight==%d\n", flags->num_wight);
    // printf("flags->num_wight2==%d\n", flags->num_wight2);
    // printf("flags->flag_num2==%d\n", flags->flag_num2);
    // // printf("flags->precision==%d\n", flags->precision);
    // printf("flags->num_wight==%d\n", flags->num_wight);
    // printf("nimberrr==%d\n", number);
    // printf("\n");

    if ((flags->flag_space)&&(number>=0))
    {
        s21_putchar_to_str(' ', str);
        if ((number==0)&&(!flags->precision)){
            s21_putchar_to_str('0', str);
        }
    }

    if (number<0){
        flags->num_wight-=1;
        number *=-1;
    }


    
    if ((flags->sign) && (num_sign > 0) && (!flags->wight))
    {
        s21_putchar_to_str('+', str);
    }

    else if ((num_sign < 0) && (!flags->sign) && (flags->alignment) && (!flags->flag_num2))
    {
        s21_putchar_to_str('-', str);
    }

    else if ((num_sign<0) && (!flags->wight) && (!flags->sign)  && (!flags->alignment))
    {
        s21_putchar_to_str('-', str);
    }

    else if((num_sign<0) && (!flags->sign) && (flags->flag_num2) && (flags->wight)){

        s21_putchar_to_str('-', str);
    }

        
    while (number != 0)
    {
        long int digit = (long int)number % 10;
        chars[index++] = digit + '0';
        number /= 10;
    }


    if(((flags->num_wight - flags->num_wight2)>index)&&(flags->flag_num2) && (!flags->alignment))
    {
        for(int j=0; j<(flags->num_wight-flags->num_wight2); j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }

    // printf("num_wight==%d\n", flags->num_wight);
    // printf("num_wight2==%d\n", flags->num_wight2);
    // printf("\n");

    if ((flags->wight)&&(!flags->precision)&&(!flags->flag_num2)&&(!flags->sign)&&(!flags->alignment)){
        
        if((flags->wight))
        {
            for(int j=index; j<flags->num_wight; j++)
            {   
                s21_putchar_to_str(' ', str);
            }
        }            
    }


    if(flags->sign)
    {
        
        if (num_sign>0)
        {
            flags->num_wight-=1;
        }
        
        if((flags->wight)&&(!flags->precision))
        {
            //flags->num_wight+=1;
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
        // printf("precision==%d\n", precision);
        // printf("\n");
        // printf("iundex==%d\n", index);

        for (int i=0;i<(precision);i++)
        {
            s21_putchar_to_str('0', str);
        }

    }


    

    // printf("flags->flag_num2==%d\n", flags->flag_num2);
    // printf("flags->wight==%d\n", flags->wight);
    // printf("flags->alignment==%d\n", flags->alignment);
    // printf("\n");


    if ((num_sign<0) && (!flags->sign) && (flags->wight) &&(!flags->alignment) && (!flags->flag_num2))
    {
        s21_putchar_to_str('-', str);
    }
    

    for (int i = index - 1; i >= 0; i--)
    {
        s21_putchar_to_str(chars[i], str);
    }

    if(num_sign==0){
        s21_putchar_to_str('0', str);
    }

    if (flags->alignment)
    {

        if ((flags->flag_space) && (num_sign>0)){
            flags->num_wight-=1;
        }
        for(int j=index; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
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


void convertfloatToString(char *str, structs *flags, va_list args)
{
    // long double number = va_arg(args, double);
    char chars[20];
    int index = 0;
    int index2=0;
    long double number;

    if (flags->flag_l){
        number=va_arg(args,long double);
    }
    else{
        number=va_arg(args, double);
    }

    long double num_sign=number;
    int precision;


    // if ((flags->flag_space)&&(number>=0))
    // {
    //     s21_putchar_to_str(' ', str);

    // }

    // printf("number22===%.10Lf\n", number);
    // printf("\n");

    // printf("flag->space==%d\n", flags->flag_space);

    if(!flags->precision)
    {
        precision=6;
    }

    else if(!flags->flag_num2)
    {
        precision=flags->num_wight;   
    }
    else{
        precision=flags->num_wight2; 
    }

    // printf("presicion==%d\n", precision);
    
    int count=countDigits(number,precision); // считаем количество цифр
    // printf("presicion==%d\n", precision);

    // printf("count==%d\n", count);
    // printf("flags->num_wight==%d\n", flags->num_wight);
    // printf("\n");

    if ((flags->flag_space)&&(number>=0))
    {
        s21_putchar_to_str(' ', str);
    }

    if (number<0){
        number *=-1;
        count+=1;
    }


    if (number == 0)
    {
        // s21_putchar_to_str('0', str);
    }

    else
    {
        if ((flags->sign) && (num_sign > 0) && (!flags->wight))
        {
            s21_putchar_to_str('+', str);
        }

        else if ((num_sign < 0) && (!flags->sign) && (flags->alignment) && (!flags->flag_num2))
        {
            s21_putchar_to_str('-', str);
        }

        else if ((num_sign<0) && (!flags->wight) && (!flags->sign)  && (!flags->alignment))
        {
            s21_putchar_to_str('-', str);
        }

        else if((num_sign<0) && (!flags->sign) && (flags->flag_num2) && (flags->wight)&&(count>flags->num_wight)&&(!flags->alignment)){
            s21_putchar_to_str('-', str);
        }
        else if((num_sign<0) && (!flags->sign) && (flags->flag_num2) && (flags->wight)&&(flags->alignment)){
            s21_putchar_to_str('-', str);
        }
  


    }

    // Округляем число до нужной точности
    double multiplier = pow(10, precision);
    number = round(number * multiplier) / multiplier;
    long int int_number=(long int)number;

    // printf("int_number==%ld\n", int_number);

    // printf("precision==%d\n", precision);

    while (int_number != 0)
    {
        long int digit = int_number % 10;
        chars[index++] = digit + '0';
        int_number /= 10;
    }
    
    // printf("flags->num_wight - flags->num_wight2==%d\n", flags->num_wight - flags->num_wight2);
    // printf("precision==%d\n", precision);
    // printf("index==%d\n", index);
    // printf("\n");

    //     // printf("number==%d\n", num_sign);
    //     // printf("precision==%d\n", precision);
    //     // printf("\n");
    //     // printf("iundex==%d\n", index);

    // }

    // printf("flags->num_wight==%d\n", flags->num_wight);
    // printf("flags->flag_num2==%d\n", flags->flag_num2);
    // printf("flags->num_wight2==%d\n", flags->num_wight2);
    // printf("count==%d\n", count);
    // printf("\n");
    // printf("count==%d\n", count);

    
    if((flags->num_wight>count)&&(flags->flag_num2) && (!flags->alignment))
    {

        for(int j=count; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
        // printf("d3\n");
        if ((num_sign<0)&&(flags->num_wight > count)&&(!flags->sign)){
            s21_putchar_to_str('-', str);
        }
    }

    // printf("flags->num_wight==%d\n", flags->num_wight);
    // printf("flags->num_wight2==%d\n", flags->num_wight2);
    // printf("precision==%d\n", precision);

    if ((flags->wight)&&(!flags->precision)&&(!flags->flag_num2)&&(!flags->sign)&&(!flags->alignment))
    {
        
        if((flags->wight))
        {
            for(int j=index+precision; j<flags->num_wight; j++)
            {   
                s21_putchar_to_str(' ', str);
            }
        }            
    }


    if(flags->sign)
    {
        
        if (num_sign>0)
        {
            flags->num_wight-=1;
        }
        
        if((flags->wight)&&(!flags->precision))
        {
            //flags->num_wight+=1;
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

    
    if ((num_sign<0) && (!flags->sign) && (flags->wight) &&(!flags->alignment) && (!flags->flag_num2))
    {
        s21_putchar_to_str('-', str);
    }

    for (int i = index - 1; i >= 0; i--)
    {
        s21_putchar_to_str(chars[i], str);
    }
    if(int_number==0){
        s21_putchar_to_str('0', str);
    }
    
    // printf("precision==%d\n", precision);
    if (precision >0) 
    {            // Если точность больше нуля, добавляем десятичную часть
        // Вычисляем дробную часть числа
        // printf("number==%Lf\n", number);
        long double fractionalPart = number - (long long int) number;   // Умножаем дробную часть на 10^precision, чтобы перевести ее в целое число
        //printf("fractionalInteger==%f\n", fractionalPart);
        // printf("IN pres fractionalPart==%Lf\n", fractionalPart);
        long long int fractionalInteger = round(fractionalPart * pow(10, precision));

        // printf("IN pres fractionalInteger==%lld\n",fractionalInteger);
       
        
        s21_putchar_to_str('.', str); // Добавляем разделитель десятичной части и переводим его в строку
        int count_fractionalInteger=countDigits(fractionalInteger,precision);
        if(fractionalInteger==0){
            for (int i =0; i< precision; i++)
                {
                    s21_putchar_to_str('0', str);
                
                }
        }

        else if(count_fractionalInteger<precision){
            for (int i =count_fractionalInteger; i< precision; i++)
                {
                    s21_putchar_to_str('0', str);
                
                }            
        }
        // printf("count==%d\n", countDigits(fractionalInteger,precision));

        while (fractionalInteger != 0)
        {
            long long int digit = fractionalInteger % 10;
            chars[index2++] = digit + '0';
            fractionalInteger /= 10;
        }
        
        // printf("pres==%d\n", precision);
        // printf("index2==%d\n", index2);
        // printf("count==%d\n", count);
        // printf("\n");
        
        // if (fractionalInteger==0)
        // {
        //     for(int j=0; j<flags->num_wight; j++)
        //     {
        //         s21_putchar_to_str('0', str);
        //     }
        // }
    
        for (int i = index2 - 1; i >= 0; i--)
        {
            s21_putchar_to_str(chars[i], str);
        }
        


    
    }

    if (flags->alignment)
    {

        if ((flags->flag_space) && (num_sign>0)){
            flags->num_wight-=1;
        }
        for(int j=count; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }

}



int countDigits(long double num, int precision) 
{
    // printf("num==%Lf\n", num);
    // printf("pres==%d\n", precision);

    int count = 0;
    long int integerPart = (long int)num; // Получаем целую часть числа
    // Подсчитываем количество цифр в целой части+
    if (integerPart == 0) 
    {
        count = 1; // Если число равно нулю, то у него одна цифра
    } 
    else 
    {
        while (integerPart != 0) 
        {
            count++;
            integerPart /= 10;
        }
    }

    // printf("counttt==%d\n", count);

    // Подсчитываем количество цифр в дробной части
    if (precision>0)
    {

        
        double fractionalPart = num - (long int)num;
        long fractionalInteger = round(fractionalPart * pow(10, precision));
        
        // printf("fractionalInteger==%ld\n", fractionalInteger);

        if(fractionalInteger)
        {
            count+=1;
        }
        // printf("counttt==%d\n", count);

        while(fractionalInteger != 0) 
        {
            count++;
            int digit = fractionalInteger % 10;
            fractionalInteger /= 10;
        }
    }
    // printf("num==%Lf\n", num);
    //printf("counttt3==%d\n", count);

    return count;
}


double roundToDec(double num, int dec)
{
    double multi = pow(10, dec);
    double rounded = (round(num * multi)) / multi;
    return rounded;
}


void convertStringToString(char *str,structs *flags, va_list args)
{

    char* s = va_arg(args, char *);

    int len = strlen(s);
    int precision;
    // printf("flags->num_wight==%d\n", flags->num_wight);
    // printf("flags->num_wight2==%d\n", flags->num_wight2);
    // printf("\n");

    if ((flags->wight) && (!flags->alignment))
    {
        for(int j=len; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }    
    
    if ((flags->precision))
    {   
        // printf("flags->num_wight==%d\n", flags->num_wight);
        // printf("flags->num_wight2==%d\n", flags->num_wight2);
        // printf("\n");
        
        if ((flags->flag_num2)&&((flags->num_wight-flags->num_wight2)>0))
        {
            precision=flags->num_wight - flags->num_wight2;
        }
        // else if (((flags->flag_num2) && (flags->num_wight-flags->num_wight2<0)))
        // {
            
        //     precision=(flags->num_wight2-len);
            
        // }

        else if (!flags->flag_num2)
        {
            precision= flags->num_wight ;
        }
        else
        {
            //printf("donerrrrr2222222r\n");
            precision=flags->num_wight-len;
        }
    
        // printf("precision==%d\n", precision);
        if((!flags->alignment)&&((flags->num_wight-flags->num_wight2)>0))
        {
            for (int i=0;i<(precision);i++)
            {
                s21_putchar_to_str(' ', str);
            }
        }

    }

    // printf("precision==%d\n", precision);
    if ((!flags->flag_num2)&&(flags->wight)&&(flags->precision))
    {
        for (int i = 0; i < flags->num_wight; i++)
        {
            s21_putchar_to_str(s[i], str);
        }
    }
    
    else if ((flags->flag_num2)&&(len>flags->num_wight2))
    {
        for (int i = 0; i < flags->num_wight2; i++)
        {
            s21_putchar_to_str(s[i], str);
        }

    }
    else if(((flags->flag_num2)&&(len<flags->num_wight2))){
        for (int i = 0; i < len; i++)
        {
            s21_putchar_to_str(s[i], str);
        }        
    }
    else if (!flags->precision)
    {
        for (int i = 0; i < len; i++)
        {
            s21_putchar_to_str(s[i], str);
        }
    }

    if ((flags->alignment))
    {
        if(!flags->flag_num2)
        {
        
        for(int j=len; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }        

        }
        else if((flags->flag_num2))
        {
        for(int j=0; j<precision; j++)
        {
            s21_putchar_to_str(' ', str);
        }      
        }
    }

}

int convertCharToString(char c,char *str,structs *flags)
{ 
    int precision;
    // printf("flags->num_wight==%d\n", flags->num_wight);
    // printf("flags->num_wight2==%d\n", flags->num_wight2);
    // printf("\n");
    // printf("flags->aligment===%d\n", flags->alignment);

    
    if ((flags->precision))
    {   
        // printf("flags->num_wight==%d\n", flags->num_wight);
        // printf("flags->num_wight2==%d\n", flags->num_wight2);
        // printf("\n");
        
        // if ((flags->flag_num2)&&((flags->num_wight-flags->num_wight2)>0))
        // {
        //     precision=flags->num_wight2;
        // }
        // else if (((flags->flag_num2) && (flags->num_wight-flags->num_wsight2<0)))
        // {
            
        //     precision=(flags->num_wight2-len);
            
        // }


    
        precision= flags->num_wight ;
        
        // else
        // {2
        //     //printf("donerrrrr2222222r\n");
        //     precision=flags->num_wight;
        // }
    
        // printf("precision==%d\n", precision);
        if((!flags->alignment)&&((flags->num_wight-flags->num_wight2)>0))
        {
            for (int i=0;i<precision;i++)
            {
                s21_putchar_to_str(' ', str);
            }
        }

    }

    // printf("precision==%d\n", precision);

    if((flags->wight)&&(!flags->flag_num2)&&(!flags->alignment)){
        for (int i=1;i<flags->num_wight;i++)
        {
            s21_putchar_to_str(' ', str);
        }
    }
    
        
    s21_putchar_to_str(c, str);

    // printf("flags->wight==%d\n", flags->num_wight);
    // printf("flag 2num==%d\n", flags->num_wight2);
    // printf("aligment==%d\n", flags->alignment);
    if ((flags->alignment))
    {
        // prin""tf("flags->wight==%d", flags->wight);
        
        if(!flags->flag_num2)
        {
            // printf("flags->wight==%d", flags->wight);
            for(int j=1; j<flags->num_wight; j++)
            {
                s21_putchar_to_str(' ', str);
                // printf("size==%ld\n", strlen(str));
            }        

        }
        else if(flags->flag_num2)
        {
            for(int j=1; j<precision; j++)
            {
                s21_putchar_to_str(' ', str);
            }      
        }
        // printf("size==%ld\n", strlen(str));
    }
      
    return 0;
}




int main()
{
    char str[1250];
    char stt[500];
    char ss[50] = "End strok";
    int a = 0;

    printf("Test1\n");
    sprintf(stt, "%d%d%d%d", a,a,a,a);
    s21_sprintf(str,"%d%d%d%d", a,a,a,a);

    printf("origin0 == %s\n", stt);
    printf("my func == %s\n", str);
    printf("\n");
    // printf("origin0 == %ld\n", strlen(stt));
    // printf("my func == %ld\n", strlen(str));
    // printf("\n");
    // printf("origin0 == %d\n", "%f", 0.0001);
    // printf("my func == %d\n", "%f", 0.0001);
    // printf("\n");
    
    // printf("Test1\n");
    // sprintf(stt, "% f", a);
    // s21_sprintf(str,"% f", a);
    // printf("origin0 == %s\n", stt);
    // printf("my func == %s\n", str);
    // printf("\n");
    // printf("origin0 == %ld\n", strlen(stt));
    // printf("my func == %ld\n", strlen(str));
    // printf("\n");
    // printf("origin0 == %d\n", "% f", 0);
    // printf("my func == %d\n", "% f", 0);
    // printf("\n");
    return 0;
}