#include <string.h>
#include <stdio.h>
#include <stdarg.h>

int s21_putchar_to_str(const char c, char *str);
void convertNumberToChars(int number,char *str);
int check_characteristics(const char c, va_list args, char *str);

int s21_sprintf(char *str, const char *format,...)
{
    int result;
    result=0;
    int i=-1;
    str[0]='\0';
    va_list args;
    va_start(args,format);
    
    while (format[++i]!='\0')
    {
        if(format[i]!='%')
        {
            result=s21_putchar_to_str(format[i],str);
        }
        else if(format[i]=='%' && format[i+1])
        {
            check_characteristics(format[++i],args,str);
        }
        
    
    }
    va_end(args);
    return result;
}

int s21_putchar_to_str(const char c, char *str) {
    while (*str) {
        str++;
    }
    *str = c;
    str++;
    *str = '\0';
    return 1;
}

int check_characteristics(const char c, va_list args, char *str)
{
    int d;
    switch (c)
    {
        case 'd':
            d=va_arg(args,int);
            convertNumberToChars(d,str);
            break;
        default:
            break;
    }
}


void convertNumberToChars(int number,char *str) {
    char chars[10];
    int index = 0; 

    if (number == 0) {
        chars[index++] = '0'; 
    } else {

        while (number != 0) {
            int digit = number % 10;
            chars[index++] = digit + '0';

            number /= 10; 
        }
    }

    for (int i = index - 1; i >= 0; i--) {
        s21_putchar_to_str(chars[i],str);
    }
}

int main(){
    char str[125];
    char stt[500];
    int age=512312;
    unsigned int u=-5;
    int a=123;
    double money=20.3;
    s21_sprintf(str,"My age is %d is my mony\n", age);
    sprintf(stt,"My age is %d is my mony\n", age);
    printf("origin = %s\n",stt);
    printf("my func= %s\n",str);
    return 0;
}


