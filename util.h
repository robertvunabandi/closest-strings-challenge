/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#pragma once

#include <stdbool.h>
#include <time.h>

#define ALWAYS_INLINE __attribute__((always_inline))

// Defining a way to debug print, which only work when
// debug is defined. Found this on stack overflow:
// https://stackoverflow.com/questions/1941307/debug-print-macro-in-c
#ifdef DEBUG
# define DEBUG_PRINT(fmt, args...) fprintf(stderr, "%s:%d:%s: " fmt, __FILE__, __LINE__, __func__, ## args)
#else
# define DEBUG_PRINT(fmt, args...)
#endif

/**
 * Returns true when the two given strings are equal,
 * and false otherwise.
 */
bool String_equal(char *str1, char *str2);

/**
 * Returns true when str is contained in the array str_arr
 * of size length.
 */
bool String_in_array(char *str, char **str_arr, int length);

/**
 * Report the time with the given information string.
 */
void report_time(struct timespec *start, struct timespec *end, char *prefix);

#define NUM_BITS_IN_BYTE 8

typedef enum hash_t {
  INTEGER_HT,
  STRING_HT
} hash_t;

int hash(void *value, hash_t vtype);
