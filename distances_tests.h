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
#include "./util.h"

#include <stdbool.h>

#include "./tests.h"
#include "./distances.h"

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
