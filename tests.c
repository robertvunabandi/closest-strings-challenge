/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include "./tests.h"

#include "./distances.h"
#include "./util.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

//
// How to Test:
// Here's how testing this works. Write a function that
// takes no parameter and returns a boolean. That function
// is a test, so by convention, name it something like 
// "test<TrueTestName>". Then, scroll all the way to the 
// `main(int argc, char *argv[])` function section and add 
// the line `Test_run(*test<TrueTestName>, "test<TrueTestName>")`
// wherever appropriate.
//

// Here's a sample test that always passes.
bool testSampleTest() {
  Test_ensureTrue(true);
  Test_ensureFalse(false);
  Test_ensureEqualInt(1, 1);
  return true;
}

//
// Testing `distances.h` Definitions
//

#define HAMMING_DISTANCE_VA_ARGS_MSG(s1, s2) "%s%s%s failed for strings %s{\"%s\", \"%s\"}%s\n", C_BOLD_BLACK, "hammingDistance", C_NC, C_BOLD_WHITE, s1, s2, C_NC
#define RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2) "%s%s%s failed for strings %s{\"%s\", \"%s\"}%s\n", C_BOLD_BLACK, "relvativeDistance", C_NC, C_BOLD_WHITE, s1, s2, C_NC
#define ROT_RELATIVE_DISTANCE_VA_ARGS_MSG(s1, s2) "%s%s%s failed for strings %s{\"%s\", \"%s\"}%s\n", C_BOLD_BLACK, "rotRelvativeDistance", C_NC, C_BOLD_WHITE, s1, s2, C_NC

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
  int numGroupsFailed =  numGroups - numGroupsPassed;
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

