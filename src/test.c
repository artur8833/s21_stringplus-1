#include <stdio.h>
#include <string.h>

int main() {
  const char* testStrValue1 = "mem\n   ke";
  const char* testStrValue2 = "mem kek";

  size_t testCountValue2 = 12;

  printf("%d", memcmp(testStrValue1, testStrValue2, testCountValue2));
  return 0;
}