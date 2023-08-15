#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "../string/s21_sprintf.h"

Suite *memchrTest(void);
Suite *memcmpTest(void);
Suite *memcpyTest(void);
Suite *memsetTest(void);
Suite *sprintfTest(void);
Suite *strchrTest(void);
Suite *strcspnTest(void);  // 1
Suite *strerrorTest(void);
Suite *strlenTest(void);
Suite *strncatTest(void);  // 2
Suite *strncmpTest(void);
Suite *strncpyTest(void);  // 3
Suite *strpbrkTest(void);
Suite *strrchrTest(void);
Suite *strstrTest(void);
Suite *strtokTest(void);
Suite *insertTest(void);
Suite *tolowerTest(void);
Suite *toupperTest(void);
Suite *trimTest(void);
#endif