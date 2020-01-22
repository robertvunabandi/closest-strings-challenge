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

#include "./tests.h"

#include "./closest_strings.h"

#include "./closest_strings_tests.h"
#include "./distances_tests.h"
#include "./util_tests.h"

#include <string.h>
#include <time.h>

//
// How to Test:
// A single test is essentially a boolean function that returns true when
// it passes and false otherwise. By convention, we write the name like
// "test<TrueTestName>". Then, to test that function, we add inside the
// `main(int argc, char *argv[])` function below the line 
// `Test_run(*test<TrueTestName>, "test<TrueTestName>")` wherever appropriate.
// As a sample, the `testSampleTest` shows you how to write one test. Now,
// to prevent writing all the tests in this file and making it super huge and
// unreadable, one can write the test inside a `<someFName>_tests.h` header
// file, in it include whatever is necessary to run those tests and include
// the `tests.h` to make use of the testEnsure macros, and finally include
// that header into this file and then inside the main function, run the
// specific tests where appropriate. This is an extra step one has to do, 
// because this is C and you just gotta make things explicit in C.
//

// Here's a sample test that always passes.
bool testSampleTest() {
  Test_ensureTrue(true);
  Test_ensureFalse(false);
  Test_ensureEqualInt(1, 1);
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
