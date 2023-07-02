#ifndef __S21_SIZE_TYPE__
#define __S21_SIZE_TYPE__ long unsigned int
#endif
typedef __S21_SIZE_TYPE__ s21_size_t;
#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *s21_strtok(char *str, const char *delim);
char *s21_strstr(const char *haystack, const char *needle);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
// char *s21_strerror (int errnum);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strchr(const char *str, int c);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memchr(const void *, int, s21_size_t);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
s21_size_t s21_strlen(const char *);

#endif