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

/**
 * The hash function, for a given valid hash type hash_t, is defined such that
 * if two objects (which must be immutable) of that type are behaviorally equal,
 * then their hash values are also equal. Behavioral equality here is used as
 * defined in MIT course 6.031 in the Equality section. It says, 
 * 
 *   behavioral equality means that two references cannot be distinguished now 
 *   or in the future, even if a mutator is called to change the state of one 
 *   object but not the other. This tests whether the two references will 
 *   'behave' the same, in this and all future states.
 * 
 * See http://web.mit.edu/6.031/www/fa19/classes/15-equality/#equality_of_mutable_types 
 */
int hash(void *value, hash_t vtype);
