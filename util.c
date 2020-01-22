/**
 * Copyright (c) 2020 Robert M. Vunabandi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "util.h"

#include <stdio.h>
#include <string.h>

bool String_equal(char *str1, char *str2) {
  return strcmp(str1, str2) == 0;
}

bool String_in_array(char *str, char **str_arr, int length) {
  for (int i = 0; i < length; i++) {
    if (String_equal(str, str_arr[i])) {
      return true;
    }
  }
  return false;
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
