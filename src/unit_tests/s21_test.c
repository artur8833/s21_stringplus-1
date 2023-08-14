#include "s21_test.h"

int main() {
  int number_failed = 0;

  Suite *test[] = {
    memchrTest(),
    memcmpTest(),
    memcpyTest(),
    memsetTest(),
    sprintfTest(),
    strchrTest(),
    strcspnTest(), // 1
    strerrorTest(),
    strlenTest(),
    strncatTest(), // 2
    strncmpTest(),
    strncpyTest(), // 3
    strpbrkTest(),
    strrchrTest(),
    strstrTest(),
    strtokTest(),
    
    insertTest(),  
    tolowerTest(),
    toupperTest(),
    trimTest(),
    NULL
  };

  for (int i = 0; test[i] != NULL; i++) {
    printf("\n\n");
    SRunner *sr = srunner_create(test[i]);

    srunner_run_all(sr, CK_VERBOSE);

    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  return (number_failed == 0) ? 0 : 1;
}
