/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include "./tests.h"

#include "./closest_strings.h"
#include "./distances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//
// How to Test:
// Here's how testing this works. Write a function that takes no parameter
// and returns a boolean. That function is a test, so by convention, name
// it something like "test<TrueTestName>". Then, scroll all the way to the
// `main(int argc, char *argv[])` function section and add the line
// `Test_run(*test<TrueTestName>, "test<TrueTestName>")` wherever appropriate.
//

/// TODO: THIS FILE IS HUGE. It should be broken down. Here's an idea.
/// Run the tests inside tests.c just like now. However, define the tests
/// in a different file. E.g., inside distances_tests.c. Issue is that we'd
/// have to write a header for each test file. What if they are included only
/// once?

// Here's a sample test that always passes.
bool testSampleTest() {
  Test_ensureTrue(true);
  Test_ensureFalse(false);
  Test_ensureEqualInt(1, 1);
  return true;
}

//
// Testing `util.h` Definitions
//

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

//
// Testing `distances.h` Definitions
//

#define HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2)                                         \
  "%s%s%s failed for strings %s{\"%s\", \"%s\"}%s\n", C_BOLD_BLACK,                  \
    "hammingDistance", C_NC, C_BOLD_WHITE, s1, s2, C_NC
#define RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2)                                        \
  "%s%s%s failed for strings %s{\"%s\", \"%s\"}%s\n", C_BOLD_BLACK,                  \
    "relvativeDistance", C_NC, C_BOLD_WHITE, s1, s2, C_NC
#define ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2)                                    \
  "%s%s%s failed for strings %s{\"%s\", \"%s\"}%s\n", C_BOLD_BLACK,                  \
    "rotRelvativeDistance", C_NC, C_BOLD_WHITE, s1, s2, C_NC
#define PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2)                                \
  "%s%s%s failed for strings %s{\"%s\", \"%s\"}%s\n", C_BOLD_BLACK,                  \
    "pairwiseHammingDistance", C_NC, C_BOLD_WHITE, s1, s2, C_NC

bool testHammingDistanceZero() {
  // expected is the same everywhere
  int expected = 0;

  char *s1 = "h";
  char *s2 = "h";
  int result = hammingDistance(s1, s2, 1);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  s1 = "he";
  s2 = "he";
  result = hammingDistance(s1, s2, 2);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  s1 = "hello";
  s2 = "hello";
  result = hammingDistance(s1, s2, 5);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  s1 = "sdglerglktgergposvdwef";
  s2 = "sdglerglktgergposvdwef";
  result = hammingDistance(s1, s2, 22);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  return true;
}

bool testHammingDistanceOne() {
  // expected is the same everywhere
  int expected = 1;

  char *s1 = "h";
  char *s2 = "e";
  int result = hammingDistance(s1, s2, 1);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  s1 = "he";
  s2 = "hb";
  result = hammingDistance(s1, s2, 2);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  s1 = "hello";
  s2 = "hexlo";
  result = hammingDistance(s1, s2, 5);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  s1 = "hello";
  s2 = "heloo";
  result = hammingDistance(s1, s2, 5);
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  return true;
}

bool testHammingDistanceRandom1() {
  char *s1 = "hello";
  char *s2 = "eeloa";
  int result = hammingDistance(s1, s2, 5);
  int expected = 3;
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  return true;
}

bool testHammingDistanceRandom2() {
  char *s1 = "hellothere";
  char *s2 = "eeloathera";
  int result = hammingDistance(s1, s2, 10);
  int expected = 4;
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  return true;
}

bool testHammingDistanceRandom3() {
  char *s1 = "coffeeandtea";
  char *s2 = "coffeaandtee";
  int result = hammingDistance(s1, s2, 12);
  int expected = 2;
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  return true;
}

bool testHammingDistanceRandom4() {
  char *s1 = "aaaaaaabbbbbe";
  char *s2 = "rrrrrrrrrraae";
  int result = hammingDistance(s1, s2, 13);
  int expected = 12;
  Test_ensureEqualIntMsg(expected, result, HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));

  return true;
}

bool testRelativeDistanceZero() {
  // expected is the same everywhere
  int expected = 0;

  char *s1 = "h";
  char *s2 = "h";
  int length = 1;
  int result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "he";
  s2 = "he";
  length = 2;
  result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hello";
  s2 = "hello";
  length = 5;
  result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "sdglerglktgergposvdwef";
  s2 = "sdglerglktgergposvdwef";
  length = 22;
  result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRelativeDistanceOne() {
  // expected is the same everywhere
  int expected = 1;

  char *s1 = "h";
  char *s2 = "g";
  int length = 1;
  int result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "he";
  s2 = "hd";
  length = 2;
  result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hello";
  s2 = "hemlo";
  length = 5;
  result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hello";
  s2 = "helko";
  length = 5;
  result = relativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRelativeDistanceRandom1() {
  char *s1 = "d";
  char *s2 = "a";
  int length = 1;
  int result = relativeDistance(s1, s2, length);
  int expected = 3;
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRelativeDistanceRandom2() {
  char *s1 = "dz";
  char *s2 = "aa";
  int length = 2;
  int result = relativeDistance(s1, s2, length);
  int expected = 28;
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRelativeDistanceRandom3() {
  char *s1 = "aaaaaaaa";
  char *s2 = "aabcdedc";
  int length = 8;
  int result = relativeDistance(s1, s2, length);
  int expected = 15;
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRelativeDistanceRandom4() {
  char *s1 = "aaaaaaaa";
  char *s2 = "bcaadecd";
  int length = 8;
  int result = relativeDistance(s1, s2, length);
  int expected = 15;
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = relativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRotRelativeDistanceZero() {
  // expected is the same everywhere
  int expected = 0;

  char *s1 = "h";
  char *s2 = "h";
  int length = 1;
  int result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "he";
  s2 = "he";
  length = 2;
  result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hello";
  s2 = "hello";
  length = 5;
  result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "sdglerglktgergposvdwef";
  s2 = "sdglerglktgergposvdwef";
  length = 22;
  result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRotRelativeDistanceOne() {
  // expected is the same everywhere
  int expected = 1;

  char *s1 = "h";
  char *s2 = "g";
  int length = 1;
  int result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "he";
  s2 = "hd";
  length = 2;
  result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hello";
  s2 = "hemlo";
  length = 5;
  result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hello";
  s2 = "helko";
  length = 5;
  result = rotRelativeDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRotRelativeDistanceRandom1() {
  char *s1 = "d";
  char *s2 = "z";
  int length = 1;
  int result = rotRelativeDistance(s1, s2, length);
  int expected = 4;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRotRelativeDistanceRandom2() {
  char *s1 = "dz";
  char *s2 = "aa";
  int length = 2;
  int result = rotRelativeDistance(s1, s2, length);
  int expected = 4;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRotRelativeDistanceRandom3() {
  char *s1 = "aaaa";
  char *s2 = "atau";
  int length = 4;
  int result = rotRelativeDistance(s1, s2, length);
  int expected = 13;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRotRelativeDistanceRandom4() {
  char *s1 = "ff";
  char *s2 = "zg";
  int length = 2;
  int result = rotRelativeDistance(s1, s2, length);
  int expected = 7;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testRotRelativeDistanceRegression1() {
  char *s1 = "a";
  char *s2 = "b";
  int length = 1;
  int result = rotRelativeDistance(s1, s2, length);
  int expected = 1;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "b";
  s2 = "b";
  result = rotRelativeDistance(s1, s2, length);
  expected = 0;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "c";
  s2 = "b";
  result = rotRelativeDistance(s1, s2, length);
  expected = 1;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "d";
  s2 = "b";
  result = rotRelativeDistance(s1, s2, length);
  expected = 2;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "e";
  s2 = "b";
  result = rotRelativeDistance(s1, s2, length);
  expected = 3;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}
bool testRotRelativeDistanceRegression2() {
  char *s1 = "b";
  char *s2 = "c";
  int length = 1;
  int result = rotRelativeDistance(s1, s2, length);
  int expected = 1;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "c";
  result = rotRelativeDistance(s1, s2, length);
  expected = 0;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "d";
  result = rotRelativeDistance(s1, s2, length);
  expected = 1;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "e";
  result = rotRelativeDistance(s1, s2, length);
  expected = 2;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "f";
  result = rotRelativeDistance(s1, s2, length);
  expected = 3;
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = rotRelativeDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testPairwiseHammingDistanceZero() {
  // expected is the same everywhere
  int expected = 0;

  char *s1 = "h";
  char *s2 = "h";
  int length = 1;
  int result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hh";
  s2 = "hh";
  length = 2;
  result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "bbbbb";
  s2 = "bbbbb";
  length = 5;
  result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "zzzzzzzzzzzzzzzzzzzzzz";
  s2 = "zzzzzzzzzzzzzzzzzzzzzz";
  length = 22;
  result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testPairwiseHammingDistanceOneLetterDiffer() {
  // expected is the same everywhere

  char *s1 = "h";
  char *s2 = "g";
  int length = 1;
  int expected = 1;
  int result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "he";
  s2 = "he";
  length = 2;
  expected = 4;
  result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "he";
  s2 = "hd";
  length = 2;
  expected = 5;
  result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  s1 = "hello";
  s2 = "hemlo";
  length = 5;
  expected = 59;
  result = pairwiseHammingDistance(s1, s2, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testPairwiseHammingDistanceRandom1() {
  char *s1 = "d";
  char *s2 = "z";
  int length = 1;
  int result = pairwiseHammingDistance(s1, s2, length);
  int expected = 1;
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testPairwiseHammingDistanceRandom2() {
  char *s1 = "dz";
  char *s2 = "aa";
  int length = 2;
  int result = pairwiseHammingDistance(s1, s2, length);
  int expected = 6;
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testPairwiseHammingDistanceRandom3() {
  char *s1 = "aaaa";
  char *s2 = "atau";
  int length = 4;
  int result = pairwiseHammingDistance(s1, s2, length);
  int expected = 18;
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

bool testPairwiseHammingDistanceRandom4() {
  char *s1 = "fff";
  char *s2 = "zgf";
  int length = 3;
  int result = pairwiseHammingDistance(s1, s2, length);
  int expected = 11;
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2));
  result = pairwiseHammingDistance(s2, s1, length);
  Test_ensureEqualIntMsg(expected, result, PAIRWISE_HAMMING_DISTANCE_VA_ARGS_MSG(s2, s1));

  return true;
}

//
// Testing `closest_strings.h` Main function
//

#define LARGE_ENOUGH_STRING_SIZE 1000
#define CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(e_k, r_k)                                   \
  "%sclosest_strings%s failed. Expected csr->k to be %s%d%s, but instead was %s%d%s\n",  \
    C_BOLD_BLACK, C_NC, C_BOLD_CYAN, e_k, C_NC, C_BOLD_RED, r_k, C_NC
#define CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(e_m, r_m)                                   \
  "%sclosest_strings%s failed. Expected csr->m to be %s%d%s, but instead was %s%d%s\n",  \
    C_BOLD_BLACK, C_NC, C_BOLD_CYAN, e_m, C_NC, C_BOLD_RED, r_m, C_NC
#define CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(e_l, r_l)                                     \
  "%sclosest_strings%s failed. expected strlen(csr->s) to be %s%d%s, but instead was %s%d%s\n", \
    C_BOLD_BLACK, C_NC, C_BOLD_CYAN, e_l, C_NC, C_BOLD_RED, r_l, C_NC
#define CLOSEST_STRINGS_RESULT_S_VA_ARGS_MSG(e_s, r_s)                                   \
  "%sclosest_strings%s failed. Expected csr->s to be %s%s%s, but instead was %s%s%s\n",  \
    C_BOLD_BLACK, C_NC, C_BOLD_CYAN, e_s, C_NC, C_BOLD_RED, r_s, C_NC
#define CLOSEST_STRINGS_RESULT_S_IN_ARRAY_IDX_VA_ARGS_MSG(r_s, idx)  \
  "%sclosest_strings%s failed. Expected csr->s (%s%s%s) at index %s%d%s to be in the given set but it wasn't.\n",  \
    C_BOLD_BLACK, C_NC, C_BOLD_RED, r_s, C_NC, C_BOLD_WHITE, idx, C_NC
#define CLOSEST_STRINGS_RESULT_S_IN_ARRAY_VA_ARGS_MSG(r_s)  \
  "%sclosest_strings%s failed. Expected csr->s (%s%s%s) to be in the given set but it wasn't.\n",  \
    C_BOLD_BLACK, C_NC, C_BOLD_RED, r_s, C_NC 

#define CLOSEST_STRINGS_RESULT_S_EXPECTED_CHAR_AT_TO_BE(e_c, r_c, c_idx)  \
  "%sclosest_strings%s failed. Expected csr->s[%s%d%s] (%s%c%s) to be %s%c%s, but it wasn't.\n",  \
    C_BOLD_BLACK, C_NC, C_BOLD_WHITE, c_idx, C_NC, C_BOLD_RED, r_c, C_NC, C_BOLD_CYAN, e_c, C_NC

bool testClosestStringsSameStrings() {
  char *words[] = {"aa", "aa", "aa", "aa"};
  const int num_words = 4;
  const int m = 2;
  int num_funcs = 3;
  int (*dist_funcs[3])(char *, char *, int)  = {
    &hammingDistance, 
    &relativeDistance, 
    &rotRelativeDistance
  };
  int expected_k = 0;
  int expected_m = 2;
  int expected_length = expected_m;
  char *expected_s = "aa";
  for (int i = 0; i < num_funcs; i++) {
    ClosestStringResult *csr = CSR_allocate(m);
    int result_k;
    int result_m;
    int result_length;
    // result_s has this length because strcpy needs the dest
    // string to be large enough to hold the source string it's
    // copying. Since we're copying before testing, we can't 
    // assume that the method will work correctly, so we pass 
    // in a size that's large enough. We do all this to prevent
    // segmentation faults.
    char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
    closest_string(words, num_words, m, dist_funcs[i], csr);
    result_k = csr->k;
    result_m = csr->m;
    result_length = strlen(csr->s);
    strcpy(result_s, csr->s);
    CSR_free(csr);
    // Now, test that the results match.
    Test_ensureEqualIntMsg(
      expected_k,
      result_k,
      CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
    );
    Test_ensureEqualIntMsg(
      expected_m,
      result_m,
      CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
    );
    Test_ensureEqualIntMsg(
      expected_length,
      result_length,
      CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
    );
    Test_ensureEqualStringMsg(
      expected_s,
      result_s,
      CLOSEST_STRINGS_RESULT_S_VA_ARGS_MSG(expected_s, result_s)
    );
  }
  return true;
}

bool testClosestStringsHammingDistance1() {
  char *words[] = {"ax", "by", "cz", "da", "eb"};
  const int num_words = 5;
  const int m = 2;

  int expected_k = 2;
  int expected_m = 2;
  int expected_length = expected_m;
  char *expected_s_char_0[] = {"a", "b", "c", "d", "e"};
  char *expected_s_char_1[] = {"x", "y", "z", "a", "b"};
  const int expected_s_set_length = 5;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &hammingDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  char result_0[2];
  result_0[0] = result_s[0];
  Test_ensureStringInArrayMsg(
    expected_s_char_0,
    expected_s_set_length,
    result_0,
    CLOSEST_STRINGS_RESULT_S_IN_ARRAY_IDX_VA_ARGS_MSG(result_0, 0)
  );
  char result_1[2];
  result_1[0] = result_s[1];
  Test_ensureStringInArrayMsg(
    expected_s_char_1,
    expected_s_set_length,
    result_1,
    CLOSEST_STRINGS_RESULT_S_IN_ARRAY_IDX_VA_ARGS_MSG(result_1, 1)
  );
  return true;
}

bool testClosestStringsHammingDistance2() {
  char *words[] = {"aaaa", "abaa", "acaa"};
  const int num_words = 3;
  const int m = 4;

  int expected_k = 1;
  int expected_m = 4;
  int expected_length = expected_m;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &hammingDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  char expected_char = 'a';
  // the second character can really be anything.
  int known_chars_indices[] = {0, 2, 3};
  int known_chars_length = 3;
  for (int i = 0; i < known_chars_length; i++) {
    int idx = known_chars_indices[i];
    Test_ensureEqualCharMsg(
      expected_char, 
      result_s[idx], 
      CLOSEST_STRINGS_RESULT_S_EXPECTED_CHAR_AT_TO_BE(expected_char, result_s[idx], idx)
    );
  }
  return true;
}

bool testClosestStringsRelativeDistance1() {
  char *words[] = {"ax", "by", "cz", "da", "eb"};
  const int num_words = 5;
  const int m = 2;

  int expected_k = 13;
  int expected_m = 2;
  int expected_length = expected_m;
  char *expected_s_set[] = {"cm", "dn"};
  const int expected_s_set_length = 2;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &relativeDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  Test_ensureStringInArrayMsg(
    expected_s_set,
    expected_s_set_length,
    result_s,
    CLOSEST_STRINGS_RESULT_S_IN_ARRAY_VA_ARGS_MSG(result_s)
  );
  return true;
}

bool testClosestStringsRelativeDistance2() {
  char *words[] = {"aaaa", "acaa", "aeaa"};
  const int num_words = 3;
  const int m = 4;

  int expected_k = 2;
  int expected_m = 4;
  int expected_length = expected_m;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &relativeDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  char expected_char = 'a';
  int known_chars_indices[] = {0, 2, 3};
  int known_chars_length = 3;
  for (int i = 0; i < known_chars_length; i++) {
    int idx = known_chars_indices[i];
    Test_ensureEqualCharMsg(
      expected_char, 
      result_s[idx], 
      CLOSEST_STRINGS_RESULT_S_EXPECTED_CHAR_AT_TO_BE(expected_char, result_s[idx], idx)
    );
  }

  // The second character has to be c. 
  Test_ensureEqualCharMsg(
    'c', 
    result_s[1], 
    CLOSEST_STRINGS_RESULT_S_EXPECTED_CHAR_AT_TO_BE('c', result_s[1], 1)
  );
  return true;
}

bool testClosestStringsRotRelativeDistance1() {
  char *words[] = {"ax", "by", "cz", "da", "eb"};
  const int num_words = 5;
  const int m = 2;

  int expected_k = 4;
  int expected_m = 2;
  int expected_length = expected_m;
  char *expected_s_set[] = {"ab", "ba", "cz", "dy", "ex"};
  const int expected_s_set_length = 5;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &rotRelativeDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  Test_ensureStringInArrayMsg(
    expected_s_set,
    expected_s_set_length,
    result_s,
    CLOSEST_STRINGS_RESULT_S_IN_ARRAY_VA_ARGS_MSG(result_s)
  );
  return true;
}

bool testClosestStringsRotRelativeDistance2() {
  char *words[] = {"axaa", "aaaa", "adaa"};
  const int num_words = 3;
  const int m = 4;

  int expected_k = 3;
  int expected_m = 4;
  int expected_length = expected_m;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &rotRelativeDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  char expected_char = 'a';
  int known_chars_indices[] = {0, 2, 3};
  int known_chars_length = 3;
  for (int i = 0; i < known_chars_length; i++) {
    int idx = known_chars_indices[i];
    Test_ensureEqualCharMsg(
      expected_char, 
      result_s[idx], 
      CLOSEST_STRINGS_RESULT_S_EXPECTED_CHAR_AT_TO_BE(expected_char, result_s[idx], idx)
    );
  }
  // The second character has to be a. 
  Test_ensureEqualCharMsg(
    'a', 
    result_s[1], 
    CLOSEST_STRINGS_RESULT_S_EXPECTED_CHAR_AT_TO_BE('a', result_s[1], 1)
  );
  return true;
}

bool testClosestStringsPairwiseHammingDistance1() {
  char *words[] = {"aaaa", "bbbb"};
  const int num_words = 2;
  const int m = 4;

  int expected_k = 18;
  int expected_m = 4;
  int expected_length = expected_m;
  char *expected_s_set[] = {"bbaa", "aabb"};
  const int expected_s_set_length = 2;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &pairwiseHammingDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  Test_ensureStringInArrayMsg(
    expected_s_set,
    expected_s_set_length,
    result_s,
    CLOSEST_STRINGS_RESULT_S_IN_ARRAY_VA_ARGS_MSG(result_s)
  );
  return true;
}

bool testClosestStringsPairwiseHammingDistance2() {
  char *words[] = {"aba", "aba"};
  const int num_words = 2;
  const int m = 3;

  int expected_k = 5;
  int expected_m = 3;
  int expected_length = expected_m;
  char *expected_s_set[] = {"aaa"};
  const int expected_s_set_length = 1;

  ClosestStringResult *csr = CSR_allocate(m);
  int result_k;
  int result_m;
  int result_length;
  char result_s[LARGE_ENOUGH_STRING_SIZE] = "";
  closest_string(words, num_words, m, &pairwiseHammingDistance, csr);
  result_k = csr->k;
  result_m = csr->m;
  result_length = strlen(csr->s);
  strcpy(result_s, csr->s);
  CSR_free(csr);

  Test_ensureEqualIntMsg(
    expected_k,
    result_k,
    CLOSEST_STRINGS_RESULT_K_VA_ARGS_MSG(expected_k, result_k)
  );
  Test_ensureEqualIntMsg(
    expected_m,
    result_m,
    CLOSEST_STRINGS_RESULT_M_VA_ARGS_MSG(expected_m, result_m)
  );
  Test_ensureEqualIntMsg(
    expected_length,
    result_length,
    CLOSEST_STRINGS_RESULT_LENGTH_VA_ARGS_MSG(expected_length, result_length)
  );
  Test_ensureStringInArrayMsg(
    expected_s_set,
    expected_s_set_length,
    result_s,
    CLOSEST_STRINGS_RESULT_S_IN_ARRAY_VA_ARGS_MSG(result_s)
  );
  return true;
}

// ---------------------------------------------------------------------------------

//
// Main Function:
// Make sure to add tests here so that they can be ran.
//

int main(int argc, char *argv[]) {
  // Begin testing
  Test_begin();

  // Begin testing various groups below.
  // Sample test group
  Test_group("Sample Tests");
  Test_run(*testSampleTest, "testSampleTest");

  // Util tests
  Test_group("Testing Utils");
  Test_run(*testUtilString_equalEqual, "testUtilString_equalEqual");
  Test_run(*testUtilString_equalNotEqual, "testUtilString_equalNotEqual");
  Test_run(*testUtilString_in_arrayInArray, "testUtilString_in_arrayInArray");
  Test_run(*testUtilString_in_arrayNotInArray, "testUtilString_in_arrayNotInArray");
  Test_run(*testUtilHash_integerT, "testUtilHash_integerT");
  Test_run(*testUtilHash_stringT, "testUtilHash_stringT");

  // `distances.h` group
  Test_group("Distances Tests");
  Test_run(*testHammingDistanceZero, "testHammingDistanceZero");
  Test_run(*testHammingDistanceOne, "testHammingDistanceOne");
  Test_run(*testHammingDistanceRandom1, "testHammingDistanceRandom1");
  Test_run(*testHammingDistanceRandom2, "testHammingDistanceRandom2");
  Test_run(*testHammingDistanceRandom3, "testHammingDistanceRandom3");
  Test_run(*testHammingDistanceRandom4, "testHammingDistanceRandom4");

  Test_run(*testRelativeDistanceZero, "testRelativeDistanceZero");
  Test_run(*testRelativeDistanceOne, "testRelativeDistanceOne");
  Test_run(*testRelativeDistanceRandom1, "testRelativeDistanceRandom1");
  Test_run(*testRelativeDistanceRandom2, "testRelativeDistanceRandom2");
  Test_run(*testRelativeDistanceRandom3, "testRelativeDistanceRandom3");
  Test_run(*testRelativeDistanceRandom4, "testRelativeDistanceRandom4");

  Test_run(*testRotRelativeDistanceZero, "testRotRelativeDistanceZero");
  Test_run(*testRotRelativeDistanceOne, "testRotRelativeDistanceOne");
  Test_run(*testRotRelativeDistanceRandom1, "testRotRelativeDistanceRandom1");
  Test_run(*testRotRelativeDistanceRandom2, "testRotRelativeDistanceRandom2");
  Test_run(*testRotRelativeDistanceRandom3, "testRotRelativeDistanceRandom3");
  Test_run(*testRotRelativeDistanceRandom4, "testRotRelativeDistanceRandom4");
  Test_run(*testRotRelativeDistanceRegression1, "testRotRelativeDistanceRegression1");
  Test_run(*testRotRelativeDistanceRegression2, "testRotRelativeDistanceRegression2");

  Test_run(*testPairwiseHammingDistanceZero, "testPairwiseHammingDistanceZero");
  Test_run(*testPairwiseHammingDistanceOneLetterDiffer, "testPairwiseHammingDistanceOneLetterDiffer");
  Test_run(*testPairwiseHammingDistanceRandom1, "testPairwiseHammingDistanceRandom1");
  Test_run(*testPairwiseHammingDistanceRandom2, "testPairwiseHammingDistanceRandom2");
  Test_run(*testPairwiseHammingDistanceRandom3, "testPairwiseHammingDistanceRandom3");
  Test_run(*testPairwiseHammingDistanceRandom4, "testPairwiseHammingDistanceRandom4");

  // `closest_string.h` group
  Test_group("Closest String: closest_strings");
  Test_run(*testClosestStringsSameStrings, "testClosestStringsSameStrings");
  Test_run(*testClosestStringsHammingDistance1, "testClosestStringsHammingDistance1");
  Test_run(*testClosestStringsHammingDistance2, "testClosestStringsHammingDistance2");
  Test_run(*testClosestStringsRelativeDistance1, "testClosestStringsRelativeDistance1");
  Test_run(*testClosestStringsRelativeDistance2, "testClosestStringsRelativeDistance2");
  Test_run(*testClosestStringsRotRelativeDistance1, "testClosestStringsRotRelativeDistance1");
  Test_run(*testClosestStringsRotRelativeDistance2, "testClosestStringsRotRelativeDistance2");
  Test_run(*testClosestStringsPairwiseHammingDistance1, "testClosestStringsPairwiseHammingDistance1");
  Test_run(*testClosestStringsPairwiseHammingDistance2, "testClosestStringsPairwiseHammingDistance2");

  // At the end, conclude the results of these tests
  return Test_conclude();
}

// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------

//
// Header Definitions
// See `tests.h` for details on what these functions do.
// Modify with caution.
//

static int numTests = 0;
static int numTestsPassed = 0;
static int numGroups = 0;
static int numGroupsPassed = 0;
static int numTestsInGroup = 0;
static int numTestsPassedInGroup = 0;
static struct timespec t_start, t_end;

void Test_begin() {
  clock_gettime(CLOCK_MONOTONIC, &t_start);
}

// This method is not in the public api, but it's here for making it easier
// to account for passed groups.
void Test_group_conclude() {
  if (numGroups == 0) {
    return;
  }
  if (numTestsInGroup == 0) {
    ++numGroupsPassed;
    printf("  no tests ran in this group\n");
    return;
  }
  if (numTestsPassedInGroup == numTestsInGroup) {
    ++numGroupsPassed;
  }
}

void Test_group(char *test_group_name) {
  Test_group_conclude();
  numGroups += 1;
  printf(
    "%s%s Testing Group %s%s %s%s%s\n", 
    C_BKG_BLUE, C_BOLD_WHITE, C_NC, C_NC,
    C_BOLD_WHITE, test_group_name, C_NC
  );
  numTestsInGroup = 0;
  numTestsPassedInGroup = 0;
}

void Test_start(char *test_f_name) {
  ++numTests;
  ++numTestsInGroup;
  // printf(
  //   "  Running Test #%d (%s%s%s)\n", numTestsInGroup, C_YELLOW, test_f_name, C_NC
  // );
}

void Test_run(bool (*test_f)(), char *test_f_name) {
  Test_start(test_f_name);
  bool result = (*test_f)();
  // we return true when we pass a test.
  if (result) {
    Test_pass(test_f_name);
    return;
  }
  Test_fail(test_f_name);
}

void Test_pass(char *test_f_name) {
  printf(
    "  %s%s PASS %s%s (%s%s%s)\n", 
    C_BKG_GREEN, C_BOLD_WHITE, C_NC, C_NC,
    C_BOLD_YELLOW, test_f_name, C_NC
  );
  ++numTestsPassed;
  ++numTestsPassedInGroup;
}

void Test_fail(char *test_f_name) {
  printf(
    "  %s%s FAIL %s%s (%s%s%s)\n", 
    C_BKG_RED, C_BOLD_WHITE, C_NC, C_NC,
    C_BOLD_YELLOW, test_f_name, C_NC
  );
}

bool Test_conclude() {
  // First, stop the timer and get the time.
  clock_gettime(CLOCK_MONOTONIC, &t_end);
  double tdiff = (t_end.tv_sec - t_start.tv_sec) + 1e-9 * (t_end.tv_nsec - t_start.tv_nsec);

  // Conclude the last group
  Test_group_conclude();

  // find other variables
  int numGroupsFailed = numGroups - numGroupsPassed;
  int numTestsFailed = numTests - numTestsPassed;

  // Here, we're going to display the final results the same way that
  // jest, the open source javascript testing API, does it. See:
  // https://jestjs.io/docs/en/getting-started
  printf("\n");

  // Instead of "Test Suites", we're going to use "Test Groups"
  printf("%sTest Groups:%s ", C_BOLD_WHITE, C_NC);
  if (numGroupsFailed > 0) {
    printf("%s%d failed%s, ", C_BOLD_RED, numGroupsFailed, C_NC);
  }
  printf("%s%d passed%s, ", C_BOLD_GREEN, numGroups, C_NC);
  printf("%d total\n", numGroups);

  // Print the overall Tests results.
  printf("%sTests:%s       ", C_BOLD_WHITE, C_NC);
  if (numTestsFailed > 0) {
    printf("%s%d failed%s, ", C_BOLD_RED, numTestsFailed, C_NC);
  }
  printf("%s%d passed%s, ", C_BOLD_GREEN, numTestsPassed, C_NC);
  printf("%d total\n", numTests);
  // Finally, print the time
  printf("%sTime:%s        %.3fs\n", C_BOLD_WHITE, C_NC, tdiff);
  return FAILED_EXIT_CODE;
}
