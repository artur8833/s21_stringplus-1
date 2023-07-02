
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


int s21_sprintf(const char *str, const char *format,...)
{
    
    int d;
    double f;
    unsigned int u;
    char c,*s;
    char asd[123];
    strcpy(asd,format);
    va_list(factor);
    va_start(factor,format);
    for(char *ch=asd;*ch;ch++)
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
            case'c':
                c=(char)va_arg(factor,int);
                printf("%c",c);
                break;
            case 's':
                s=va_arg(factor, char*);
                printf("%s",s);
                break;
            case 'u':
                u=va_arg(factor, unsigned int);
                printf("%u",u);
                break;
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
    char stt[50];
    char cj='+';
    int age=5;
    unsigned int u=-13;
    int a=123;
    double money=20.3;
    s21_sprintf(str,"1My age is %d %d is my mony %f ---- %c %u\n", age, a, money, cj,u);
    sprintf(stt,"My age is %d %d is my mony %f ---- %c %u\n", age, a, money, cj,u);
    printf("%s\n",stt);
    return 0;
}