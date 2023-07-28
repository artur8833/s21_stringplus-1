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

    if ((flags->flag_space)&&(num_sign>0))
    {
        s21_putchar_to_str(' ', str);
    }

    if (number<0){
        flags->num_wight-=1;
        number *=-1;
    }

    if (number == 0)
    {
        s21_putchar_to_str('0', str);
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

    if ((flags->flag_space)&&(num_sign>0))
    {
        s21_putchar_to_str(' ', str);
    }

    if (number<0){
        number *=-1;
        count+=1;
    }


    if (number == 0)
    {
        s21_putchar_to_str('0', str);
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
    
    // printf("precision==%d\n", precision);
    if (precision >0) 
    {            // Если точность больше нуля, добавляем десятичную часть
        // Вычисляем дробную часть числа
        // printf("number==%Lf\n", number);
        double fractionalPart = number - (long int) number;   // Умножаем дробную часть на 10^precision, чтобы перевести ее в целое число
        //printf("fractionalInteger==%f\n", fractionalPart);

        long fractionalInteger = round(fractionalPart * pow(10, precision));

        // printf("IN pres fractionalInteger==%ld\n", fractionalInteger);
       
        
        s21_putchar_to_str('.', str); // Добавляем разделитель десятичной части и переводим его в строку
        
        
        while (fractionalInteger != 0)
        {
            int digit = fractionalInteger % 10;
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
        for(int j=1; j<flags->num_wight; j++)
        {
            s21_putchar_to_str(' ', str);
        }
    }        
}




// int main()
// {
//     char str[1250];
//     char stt[500];
//     char ss[50] = "End strok";
//     int a=-12;

//     printf("Test1\n");
//     sprintf(stt, "Test %d Test", a);
//     s21_sprintf(str,"Test %d Test", a);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
//     printf("\n");
   
   
//     printf("Test2\n");
//     int val = 012;
//     int val2 = -017;
//     int val3 = 07464;
//     sprintf(stt, "%d Test %d Test %d", val, val, val);
//     s21_sprintf(str,"%d Test %d Test %d", val, val, val);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
//     printf("\n");


//     printf("Test3\n");
//     int val4 = 3015;
//     int val5 = 712;
//     int val6 = 99;
//     sprintf(stt, "%d Test %d Test %d", val4, val4, val4);
//     s21_sprintf(str,"%d Test %d Test %d", val4, val4, val4);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
//     printf("\n");

//     printf("Test4\n");
//     int val7 = -3015;
//     int val8 = -11234;
//     int val9 = -99;
//     sprintf(stt, "%3d Test %5d Test %10d", val7, val7, val7);
//     s21_sprintf(str, "%3d Test %5d Test %10d", val7, val7, val7);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
//     printf("\n");
   
//     printf("Test5\n");
//     int val10 = -3015;
//     int val11 = -712;
//     int val12 = -99;
//     int val13 = -38;
//     int val14 = -100;
//     sprintf(stt, "%6.5d Test %.23d Test %3.d TEST %.d %.6d", val10, val10, val10, val10, val10);
//     s21_sprintf(str,"%6.5d Test %.23d Test %3.d TEST %.d %.6d", val10, val10, val10, val10, val10);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
//     printf("\n");
    

//     printf("Test7\n");
//     int val19 = -3015;
//     int val20 = -712;
//     int val21 = -99;
//     int val22 = -2939;
//     int val23 = -0123;
//     sprintf(stt, "%0d Test %0.d Test %0.0d TEST %0d GOD %.d", val19, val19, val19, val19, val19);
//     s21_sprintf(str,"%0d Test %0.d Test %0.0d TEST %0d GOD %.d", val19, val19, val19, val19, val19);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
//     printf("\n");
    
//     printf("Test8\n");
//     int val24 = -3015;
//     int val25 = -712;
//     int val26 = -99;
//     int val27 = -2939;
//     sprintf(stt, "%+d Test %+3.d Test %+5.7d TEST %+10d", val24, val24, val24, val24);
//     s21_sprintf(str,"%+d Test %+3.d Test %+5.7d TEST %+10d", val24, val24, val24, val24);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
//     printf("\n");
    
//     printf("Test9\n");
//     int val28 = -32;
//     int val29 = -8899;
//     int val30 = -91918;
//     int val31 = -32311;
//     int val32 = -23;
//     sprintf(stt, "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d", val28, val28, val28, val28, val28);
//     s21_sprintf(str,"% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d", val28, val28, val28, val28, val28);
//     printf("origin0 == %s\n", stt);
//     printf("my func == %s\n", str);
    
//     // printf("Test10\n");
//     // int val33 = -3231;
//     // int val34 = -3231;
//     // int val35 = 3231;
//     // int val36 = 3231;
//     // sprintf(stt, "%- d Test %- 15d sdasda %- 15d sdsad %- d", val33, val34, val35, val36);
//     // s21_sprintf(str,"%- d Test %- 15d sdasda %- 15d sdsad %- d", val33, val34, val35, val36);
//     // printf("origin0 == %s\n", stt);
//     // printf("my func == %s\n", str);
//     // return 0;


    
// }


// // // float
// // int main()
// // {
// //     char str[1250];
// //     char stt[500];
// //     char ss[50] = "End strok";
// //     double num = 76.756589367;

// //     printf("Test1\n");
// //     sprintf(stt, "%f TEST %.f TEST %4f TEST %4.f TEST %5.10f!", num, num, num, num, num);
// //     s21_sprintf(str,"%f TEST %.f TEST %4f TEST %4.f TEST %5.10f!", num, num, num, num, num);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");
   
   
// //     printf("Test2\n");
// //     double num2 = -76.756589367;
// //     sprintf(stt, "%f TEST %.f TEST %3f TEST %4.f TEST %5.10f!",  num2, num2, num2, num2, num2);
// //     s21_sprintf(str,"%f TEST %.f TEST %3f TEST %4.f TEST %5.10f!",  num2, num2, num2, num2, num2);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");


// //     printf("Test3\n");
// //     long double num_long = -76.756589;
// //     sprintf(stt, "%Lf %.Lf!", num_long, num_long);
// //     s21_sprintf(str,"%Lf %.Lf!", num_long, num_long);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");

// //     printf("Test4\n");
// //     double num3 = -76.756589;
// //     sprintf(stt, "%20.10f %20.15f %-20.5f!", num, num, num);
// //     s21_sprintf(str,"%20.10f %20.15f %-20.5f!", num, num, num);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");
   

// //     printf("Test5\n");
// //     double num4 = 76.756589;
// //     sprintf(stt, "test: %5f test: %6.1f test: %8.2f!", num4, num4, num4);
// //     s21_sprintf(str,"test: %5f test: %6.1f test: %8.2f!", num4, num4, num4);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");
    



// //     printf("Test8\n");
// //     double num5 = -7648938790.756589;
// //     sprintf(stt, "test: %15.1f test: %16.2f test: %18.3f!", num5, num5, num5);
// //     s21_sprintf(str,"test: %15.1f test: %16.2f test: %18.3f!", num5, num5, num5);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");
    

// //     printf("Test9\n");
// //     sprintf(stt, "test: %10.4f test: %25.5f!", num5, num5);
// //     s21_sprintf(str,"test: %10.4f test: %25.5f!", num5, num5);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");


// //     printf("Test10\n");

// //     // double num5 = -7648938790.756589;
// //     sprintf(stt, "test: %+18.0f test: %+10.f test: %+25.f!", num5, num5,num5);
// //     s21_sprintf(str,"test: %+18.0f test: %+10.f test: %+25.f!", num5, num5,num5);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");


// //     printf("Test11\n");
// //     double num6 = -365289.3462865487;
// //     sprintf(stt, "test: %-15.4f! test: %-26.1f! test: %-18.0f!", num6, num6,num6);
// //     s21_sprintf(str,"test: %-15.4f! test: %-26.1f! test: %-18.0f!", num6, num6,num6);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");


// //     printf("Test12\n");
// //     double num7 = -365289.34628654873789362746834;
// //     sprintf(stt, "test: %15.13f! test: %26.15f!", num7, num7);
// //     s21_sprintf(str,"test: %15.13f! test: %26.15f!",num7, num7);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");


// //     printf("Test13\n");
// //     sprintf(stt, "test: %18.7f! test: %10.15f! test: %25.15f!", num7, num7,num7);
// //     s21_sprintf(str,"test: %18.7f! test: %10.15f! test: %25.15f!",num7, num7,num7);
// //     printf("origin0 == %s\n", stt);
// //     printf("my func == %s\n", str);
// //     printf("\n");

// //     return 0;
// // }