/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include <stdio.h>
#include <string.h>

#include "util.h"

bool String_equal(char *str1, char *str2) {
  return strcmp(str1, str2) == 0;
}

void report_time(struct timespec *start, struct timespec *end, char *prefix) {
  double tdiff = (end->tv_sec - start->tv_sec) + 1e-9 * (end->tv_nsec - start->tv_nsec);
  printf("%stime: %.6fs\n", prefix, tdiff);
}
