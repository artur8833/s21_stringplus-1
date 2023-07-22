#ifndef S21_TEST_H
#define S21_TEST_H
#include <check.h>
#include <string.h>

#include "../string/s21_strerror.h"
#include "../string/s21_sprintf.h"
#include "../string/s21_string.h"

Suite *memchrTest(void);
Suite *memcmpTest(void);
Suite *memsetTest(void);
Suite *sprintfTest(void);
Suite *strchrTest(void);
Suite *strerrorTest(void);
Suite *strlenTest(void);
Suite *strncmpTest(void);
Suite *strpbrkTest(void);
Suite *strrchrTest(void);
Suite *strstrTest(void);
Suite *strtokTest(void);

#endif