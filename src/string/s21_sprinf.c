#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

int s21_putchar_to_str(const char c, char *str);
void convertNumberToChars(int number,char *str);
double roundToDec(double num,int dec);
void convertStringToString(char *s,char *str);
void convertfloatToString(double number,char *str,int precision);
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
    unsigned int u;
    int d;
    float f;
    char ch,*s;
    switch (c)
    {
        case 'd':
            d=va_arg(args,int);
            convertNumberToChars(d,str);
            break;

        case'c':
            ch=(char)va_arg(args,int);
            s21_putchar_to_str(c,str);
            break;
    
        case 'f':
            f=va_arg(args,double);
            convertfloatToString(f,str,0);
            break;
        case 's':
            s=va_arg(args, char*);
            convertStringToString(s,str);
            break;
        case 'u':
            u=va_arg(args, unsigned int);
            convertNumberToChars(u,str);
            break;
        case '%':
            s21_putchar_to_str('%',str);
        default:
            break;
    }
}

void convertNumberToChars(int number,char *str) {
    char chars[10];
    int index = 0; 
    if (number == 0) {
        s21_putchar_to_str('0',str);
    } 
    else
    {
        while (number != 0) {
            if (number<0){
                number*=-1;
                s21_putchar_to_str('-',str);
            }
            int digit = (int)number % 10;
            chars[index++] = digit + '0';
            number /= 10; 
        }

        for (int i = index - 1; i >= 0; i--) {
            s21_putchar_to_str(chars[i],str);
        }

    }

}

void convertfloatToString(double number,char *str,int precision)
{
    char chars[20];
    int index=0;
    int int_number=(int)number;
    convertNumberToChars(int_number,str);
    s21_putchar_to_str('.',str);
    long double temp_float=number-int_number;
    temp_float=roundToDec(temp_float,200);
    for(int i=0;i<6;i++)
    {
        temp_float *= 10;
        int PlusNum = (int)temp_float;
        chars[index++]=PlusNum+'0';
        temp_float-=PlusNum;
    }
    for (int i=0;i<index;i++){
        s21_putchar_to_str(chars[i],str);
    }
    
}

double roundToDec(double num,int dec){
    double multi=pow(10,dec);
    double rounded=(round(num*multi))/multi;
    return rounded;
}

void convertStringToString(char *s,char *str)
{
    int len=strlen(s);
    for(int i=0;i<len;i++)
    {
        s21_putchar_to_str(s[i],str);
    }
}


int main(){
    char str[125];
    char stt[500];
    char ss[50]="End strok";
    int age=5;
    unsigned int u=54546456;
    int a=1233;
    float b=12.11334534443;
    double money=20.3;
    s21_sprintf(str,"My age %f is  is %d  my mony %s usigned=%u\n", b, a ,ss,u );
    sprintf(stt,"My age %f is  is %d  my mony %s usigned=%u\n", b, a ,ss,u );
    printf("origin = %s\n",stt);
    printf("my func= %s\n",str);
    return 0;
}


