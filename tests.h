/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#pragma once

#include "./colors.h"
#include "./util.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PASSED_EXIT_CODE 0
#define FAILED_EXIT_CODE 1

///
/// Testing API
///

/**
 * This declares a new test group. Each groups is essentially a set
 * of tests that are similar. One could think of test groups about the
 * same way as they think of test suites.
 */
void Test_group(char *test_group_name);

/**
 * Runs the test
 */
void Test_run(bool (*test_f)(), char *test_f_name);

// The functions below are indicated as @private. This means that the
// client is not supposed to call them. Only the testing framework does.

/**
 * This is called at the beginning of the `main` function in the test
 * binary to begin testing. This would set up any necessary variable
 * needed to start testing, so it must be called before everything
 * else.
 * @private
 */
void Test_begin();

/**
 * Begins the test by the given name
 * @private
 */
void Test_start(char *test_f_name);

/**
 * Tells the program that the given test passed. This may result in
 * printing things in the terminal and updating global variables. This
 * is called inside Test_run.
 * @private
 */
void Test_pass(char *test_f_name);

/**
 * Similarly, this tells the program that the given test failed. It's
 * pretty much the same as Test_pass but for failing tests.
 * @private
 */
void Test_fail(char *test_f_name);

/**
 * Called at the end of the program, this prints the overal results and
 * returns an exit code for the program. PASSED_EXIT_CODE if all tests
 * pass, and FAILED_EXIT_CODE otherwise. This must be called after all
 * tests run.
 * @private
 */
bool Test_conclude();

//
// Testing Macros:
// Instead of using "assert", we're using "ensure" because these
// macros don't actually "assert" anything. They check that they
// match and if they don't, they return false. However, these can
// generally be used the same way one would use `assert` statements
// in other programming languages when testing.
//

#define Test_ensureTrue(boolean) {                                           \
  if (!boolean) {                                                            \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      Expected %strue%s\n", C_BOLD_CYAN, C_NC);         \
    fprintf(stderr, "      Received %sfalse%s\n", C_BOLD_RED, C_NC);         \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureTrueMsg(boolean, ...) {                                   \
  if (!boolean) {                                                            \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      ");                                               \
    fprintf(stderr, __VA_ARGS__);                                            \
    fprintf(stderr, "      Expected %strue%s\n", C_BOLD_CYAN, C_NC);         \
    fprintf(stderr, "      Received %sfalse%s\n", C_BOLD_RED, C_NC);         \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureFalse(boolean) {                                          \
  if (boolean) {                                                             \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      Expected %sfalse%s\n", C_BOLD_CYAN, C_NC);        \
    fprintf(stderr, "      Received %strue%s\n", C_BOLD_RED, C_NC);          \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureFalseMsg(boolean, ...) {                                  \
  if (boolean) {                                                             \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      ");                                               \
    fprintf(stderr, __VA_ARGS__);                                            \
    fprintf(stderr, "      Expected %sfalse%s\n", C_BOLD_CYAN, C_NC);        \
    fprintf(stderr, "      Received %strue%s\n", C_BOLD_RED, C_NC);          \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureEqualInt(expected, received) {                            \
  if (received != expected) {                                                \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      Expected %s%d%s\n", C_BOLD_CYAN, expected, C_NC); \
    fprintf(stderr, "      Received %s%d%s\n", C_BOLD_RED, received, C_NC);  \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureEqualIntMsg(expected, received, ...) {                    \
  if (received != expected) {                                                \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      ");                                               \
    fprintf(stderr, __VA_ARGS__);                                            \
    fprintf(stderr, "      Expected %s%d%s\n", C_BOLD_CYAN, expected, C_NC); \
    fprintf(stderr, "      Received %s%d%s\n", C_BOLD_RED, received, C_NC);  \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureEqualChar(expected, received) {                           \
  if (received != expected) {                                                \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      Expected %s%c%s\n", C_BOLD_CYAN, expected, C_NC); \
    fprintf(stderr, "      Received %s%c%s\n", C_BOLD_RED, received, C_NC);  \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureEqualCharMsg(expected, received, ...) {                   \
  if (received != expected) {                                                \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      ");                                               \
    fprintf(stderr, __VA_ARGS__);                                            \
    fprintf(stderr, "      Expected %s%c%s\n", C_BOLD_CYAN, expected, C_NC); \
    fprintf(stderr, "      Received %s%c%s\n", C_BOLD_RED, received, C_NC);  \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureEqualString(expected, received) {                         \
  if (!String_equal(received, expected)) {                                   \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      Expected %s%s%s\n", C_BOLD_CYAN, expected, C_NC); \
    fprintf(stderr, "      Received %s%s%s\n", C_BOLD_RED, received, C_NC);  \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureEqualStringMsg(expected, received, ...) {                 \
  if (!String_equal(received, expected)) {                                   \
    fprintf(stderr, "\n");                                                   \
    fprintf(                                                                 \
      stderr, "    %s[%s:%s:%d]%s\n",                                        \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                       \
    );                                                                       \
    fprintf(stderr, "      ");                                               \
    fprintf(stderr, __VA_ARGS__);                                            \
    fprintf(stderr, "      Expected %s%s%s\n", C_BOLD_CYAN, expected, C_NC); \
    fprintf(stderr, "      Received %s%s%s\n", C_BOLD_RED, received, C_NC);  \
    fprintf(stderr, "\n");                                                   \
    return false;                                                            \
  }                                                                          \
}

#define Test_ensureStringInArrayMsg(expected_array, array_size, received, ...) {  \
  if (!String_in_array(received, expected_array, array_size)) {                   \
    fprintf(stderr, "\n");                                                        \
    fprintf(                                                                      \
      stderr, "    %s[%s:%s:%d]%s\n",                                             \
      C_BOLD_WHITE, __FILE__, __func__, __LINE__, C_NC                            \
    );                                                                            \
    fprintf(stderr, "      ");                                                    \
    fprintf(stderr, __VA_ARGS__);                                                 \
    fprintf(stderr, "      Expected argument to be in set %s{", C_BOLD_CYAN);     \
    for (int idx_ = 0; idx_ < array_size - 1; idx_++) {                           \
      fprintf(stderr, "%s, ", expected_array[idx_]);                              \
    }                                                                             \
    fprintf(stderr, "%s}%s\n", expected_array[array_size - 1], C_NC);             \
    fprintf(stderr, "      Received %s%s%s\n", C_BOLD_RED, received, C_NC);       \
    fprintf(stderr, "\n");                                                        \
    return false;                                                                 \
  }                                                                               \
}
