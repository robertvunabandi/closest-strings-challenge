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

//
// Test File Note:
// Do not include this file (or any other test file)
// anywhere except inside `tests.c`
//

#pragma once

#include "./colors.h"
#include "./distances.h"
#include "./util.h"

#include <stdbool.h>
#include <string.h>

#include "./tests.h"
#include "./closest_strings.h"

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
