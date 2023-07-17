#ifndef S21_TEST_H
#define S21_TEST_H
#include <check.h>
#include <string.h>

#include "../string/s21_strerror.h"
#include "../string/s21_sprintf.h"
#include "../string/s21_string.h"

Suite *memchrTest(void);
Suite *memcmpTest(void);
Suite *memmoveTest(void);
Suite *memsetTest(void);
Suite *sprintfTest(void);
Suite *strcatTest(void);
Suite *strchrTest(void);
Suite *strcmpTest(void);
Suite *strspnTest(void);
Suite *strerrorTest(void);
Suite *strlenTest(void);
Suite *strcatTest(void);
Suite *strncmpTest(void);
Suite *strcpyTest(void);
Suite *strpbrkTest(void);
Suite *strrchrTest(void);
Suite *strspnTest(void);
Suite *strstrTest(void);
Suite *strtokTest(void);

#endif