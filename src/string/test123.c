#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "s21_string.h"


int main() {
    char input[] = "asd5asd";

    printf("Enter a number or a character: ");
    // scanf(" %s", input);

    if (isdigit(input[2])) {
        printf("Input is an integer\n");
    } else if (isalpha(input[2])) {
        printf("Input is a character\n");
    } else {
        printf("Invalid input\n");
    }

    int i = 2147483647;
    printf("Number: %d\n", i);

    static char mass[256]; // должна быть статик что-бы вернуть указатель на строку
    char *str = "456345 0329()&*^*&$&";
    s21_size_t len_mas = s21_strspn(str, "1234567890");
    printf("%ld\n", len_mas);
    s21_memcpy(mass, str, len_mas);
 
    printf("%s\n", mass);


    return 0;
}