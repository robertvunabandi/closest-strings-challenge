/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include "util.h"

#include <stdio.h>
#include <string.h>

bool String_equal(char *str1, char *str2) {
  return strcmp(str1, str2) == 0;
}

void report_time(struct timespec *start, struct timespec *end, char *prefix) {
  double tdiff = (end->tv_sec - start->tv_sec) + 1e-9 * (end->tv_nsec - start->tv_nsec);
  printf("%stime: %.6fs\n", prefix, tdiff);
}

// Hash functions

const int HASH_P = 31;

int hash_string(char *value);

int hash(void *value, hash_t vtype) {
  switch (vtype) {
    case INTEGER_HT:
      return *(int *)value;
    case STRING_HT:
      return hash_string((char *)value);
    default:
      return -1;
  }
}

int hash_string(char *value) {
  // Got this function from the Stack Overflow response by 
  // Jerry Coffin to this post:
  // https://stackoverflow.com/questions/7666509/hash-function-for-string
  int result = 0x55555555;
  const int roll_size = 5;
  const int type_size = sizeof(int) * NUM_BITS_IN_BYTE;
  int length = strlen(value);
  for (int i = 0; i < length; i++) {
    result ^= value[i];
    result = (result << roll_size) | (result >> (type_size - roll_size));
  }
  return result;
}
