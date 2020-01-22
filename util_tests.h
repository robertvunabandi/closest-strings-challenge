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

#include "./colors.h"

#include <stdbool.h>

#include "./tests.h"
#include "./util.h"

#define STRING_EQUAL_EQUAL_VA_ARGS_MSG(s1, s2)                                                \
  "%sString_equal%s failed for equal strings %s{\"%s\", \"%s\"}%s. Result was %sfalse%s.\n",  \
  C_BOLD_BLACK, C_NC, C_BOLD_WHITE, s1, s2, C_NC, C_BOLD_RED, C_NC
#define STRING_EQUAL_NOT_EQUAL_VA_ARGS_MSG(s1, s2)                                               \
  "%sString_equal%s failed for non-equal strings %s{\"%s\", \"%s\"}%s. Result was %strue%s.\n",  \
  C_BOLD_BLACK, C_NC, C_BOLD_WHITE, s1, s2, C_NC, C_BOLD_RED, C_NC
#define STRING_IN_ARRAY_IN_VA_ARGS_MSG(str)                                                                   \
  "%sString_in_array%s failed for string %s\"%s\"%s. Result was %sfalse%s but should have been %strue%s.\n",  \
  C_BOLD_BLACK, C_NC, C_BOLD_WHITE, str, C_NC, C_BOLD_RED, C_NC, C_BOLD_CYAN, C_NC
#define STRING_IN_ARRAY_NOT_IN_VA_ARGS_MSG(str)                                                               \
  "%sString_in_array%s failed for string %s\"%s\"%s. Result was %strue%s but should have been %sfalse%s.\n",  \
  C_BOLD_BLACK, C_NC, C_BOLD_WHITE, str, C_NC, C_BOLD_RED, C_NC, C_BOLD_CYAN, C_NC
// For hash tests, all the things are equal.
#define HASH_INT_VA_ARGS_MSG(int1, int2, hash1, hash2)                                                        \
  "%shash%s failed for integers %s%d%s and %s%d%s. First had hash %s%d%s, and second had hash %s%d%s %s.\n",  \
  C_BOLD_BLACK, C_NC, C_BOLD_WHITE, int1, C_NC, C_BOLD_WHITE, int2, C_NC,                                     \
  C_BOLD_WHITE, hash1, C_NC, C_BOLD_WHITE, hash2, C_NC,                                                       \
  "which are different when they should match"
#define HASH_STRING_VA_ARGS_MSG(s1, s2, hash1, hash2)                                                        \
  "%shash%s failed for strings %s%s%s and %s%s%s. First had hash %s%d%s, and second had hash %s%d%s %s.\n",  \
  C_BOLD_BLACK, C_NC, C_BOLD_WHITE, s1, C_NC, C_BOLD_WHITE, s2, C_NC,                                        \
  C_BOLD_WHITE, hash1, C_NC, C_BOLD_WHITE, hash2, C_NC,                                                      \
  "which are different when they should match"

bool testUtilString_equalEqual() {
  char *str_arr1[] = {"abc", "ere", "sfgfsgd", "acds", ""};
  char *str_arr2[] = {"abc", "ere", "sfgfsgd", "acds", ""};
  int arr_size = 5;
  for (int i = 0; i < arr_size; i++) {
    char *str1 = str_arr1[i];
    char *str2 = str_arr2[i];
    bool result = String_equal(str1, str2);
    Test_ensureTrueMsg(result, STRING_EQUAL_EQUAL_VA_ARGS_MSG(str1, str2));
  }
  return true;
}

bool testUtilString_equalNotEqual() {
  char *str_arr1[] = {"abc", "ere", "sfgfsgd", "acds", ""};
  char *str_arr2[] = {"aac", "are", "sfgfsgdxd", "acdsd", "d"};
  int arr_size = 5;
  for (int i = 0; i < arr_size; i++) {
    char *str1 = str_arr1[i];
    char *str2 = str_arr2[i];
    bool result = String_equal(str1, str2);
    Test_ensureFalseMsg(result, STRING_EQUAL_NOT_EQUAL_VA_ARGS_MSG(str1, str2));
  }
  return true;
}

bool testUtilString_in_arrayInArray() {
  char *str_arr[] = {"abc", "ere", "sfgfsgd", "acds", ""};
  char *str_test_arr[] = {"abc", "ere", "sfgfsgd", "acds", ""};
  int arr_size = 5;
  for (int i = 0; i < arr_size; i++) {
    char *str = str_test_arr[i];
    bool result = String_in_array(str, str_arr, arr_size);
    Test_ensureTrueMsg(result, STRING_IN_ARRAY_IN_VA_ARGS_MSG(str));
  }
  return true;
}

bool testUtilString_in_arrayNotInArray() {
  char *str_arr[] = {"abcd", "erea", "sfgfgd", "acdsf", ""};
  char *str_test_arr[] = {"abc", "ere", "sfgfsgd", "acds", "f"};
  int arr_size = 5;
  for (int i = 0; i < arr_size; i++) {
    char *str = str_test_arr[i];
    bool result = String_in_array(str, str_arr, arr_size);
    Test_ensureFalseMsg(result, STRING_IN_ARRAY_NOT_IN_VA_ARGS_MSG(str));
  }
  return true;
}

bool testUtilHash_integerT() {
  int int_arr1[] = {-1, 0, 1, 5, 1453234, -12, 1345, 9991};
  int int_arr2[] = {-1, 0, 1, 5, 1453234, -12, 1345, 9991};
  int arr_size = 8;
  for (int i = 0; i < arr_size; i++) {
    int int1 = int_arr1[i];
    int int2 = int_arr2[i];
    int hash1 = hash(&int1, INTEGER_HT);
    int hash2 = hash(&int1, INTEGER_HT);
    Test_ensureEqualIntMsg(hash1, hash2, HASH_INT_VA_ARGS_MSG(int1, int2, hash1, hash2));
  }
  return true;
}

bool testUtilHash_stringT() {
  char *str_arr1[] = {"abc", "ere", "sfgfsgd", "acds", ""};
  char *str_arr2[] = {"abc", "ere", "sfgfsgd", "acds", ""};
  int arr_size = 5;
  for (int i = 0; i < arr_size; i++) {
    char *str1 = str_arr1[i];
    char *str2 = str_arr2[i];
    int hash1 = hash(str1, STRING_HT);
    int hash2 = hash(str2, STRING_HT);
    Test_ensureEqualIntMsg(hash1, hash2, HASH_STRING_VA_ARGS_MSG(str1, str2, hash1, hash2));
  }
  return true;
}
