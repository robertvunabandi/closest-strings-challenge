/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#pragma once

#include "./colors.h"

#define PASSED_EXIT_CODE 0
#define FAILED_EXIT_CODE 1

// Testing API

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
