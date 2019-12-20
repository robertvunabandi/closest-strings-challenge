/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "./distances.h"

#include "./tests.h"

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
  return true;
}

//
// Testing `distances.h` Definitions
//


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
}

void Test_start(char *test_f_name) {
  ++numTests;
  printf(
    "  running test #%d (%s%s%s)\n",
    ++numTestsInGroup, C_YELLOW, test_f_name, C_NC
  );
}

bool Test_run(bool (*test_f)(), char *test_f_name) {
  Test_start(test_f_name);
  bool result = (*test_f)();
  if (result) {
    Test_pass(test_f_name);
    return true;
  }
  Test_fail(test_f_name);
  return false;
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
    "    %s%s FAIL %s%s (%s%s%s)\n", 
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

