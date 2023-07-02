
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


int s21_sprintf(const char *str, const char *format,...)
{
    // int num_sucsess=0;
    // int j=0;
    // for (int i;i<strlen(format);i++)
    // {
    //     if ((format[i]=='%')||(format[i]==' '))
    //     {
    //     continue;
    //     }
    //     printf("%c\n",format[i]);
    // }
    
    int d;
    double f;
    char c;
    // char asd[120];
    // strcpy(asd, format);
    va_list(factor);
    va_start(factor,format);
    for(char *ch=format;*ch;ch++)
    {
        if (*ch!='%'){
            printf("%c", *ch);
            continue;
        }
        ch++;
        switch (*ch)
        {
            case 'd':
                d=va_arg(factor,int);
                printf("%d",d);
                break;
            case 'f':
                f=va_arg(factor,double);
                printf("%.1lf",f);
                break;
            // case'c':
            //     c=va_arg(factor,char);
            //     printf("%c",c);
            //     break;

            default:
                printf("%c",*ch);
                break;
        }
    }
    va_end(factor);

    return 0;
}

int main(){
    char str[50];
    int age=5;
    double money=20.3;
    s21_sprintf(str,"My age is %d is my mony %f", age, money);
    return 0;
}