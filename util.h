/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#pragma once

#include <stdbool.h>
#include <time.h>

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
 * Report the time with the given information string.
 */
void report_time(char *info, struct timespec *start, struct timespec *end);