/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#pragma once

/**
 * This is a struct that will contain the result of our program.
 * k, m, and s are used as defined in README.md.
 * 
 * Invariants:
 * - strnlen(s) = m
 * - k >= 0
 */
typedef struct ClosestStringResult {
  int k;
  int m;
  char *s;
} ClosestStringResult;

/**
 * Finds a length-`m` string `s` that has the minimum distance `k` from 
 * all the strings in the set of strings `words`. `distance` is a function
 * that takes in two character pointers and an integer for how long the
 * characters are.
 *  
 * Preconditions:
 * - the number of valid words in `words` is num_words
 * - for each `word` in `words`, strnlen(word) = m
 * - the return value of the distance function is >= 0
 * - for distance(s1, s2, q), strnlen(s1) == strnlen(s2) == q
 * 
 * Postcondition (result placed inside `csr`):
 * If `r` is the result of this call, then :
 * - distance(r->s, word, m) <= r->k for all `word` in `words`
 * - for all other length-`m` string `s`, there does not exist `word` in `words`
 *   such that distance(s, word, m) < r->k
 */
void closest_string(
  char **words, 
  const int num_words, 
  const int m,
  int (*distance)(char *, char*, int),
  ClosestStringResult *csr
);

// Allocating ClosestStringResult functions

ClosestStringResult *CSR_allocate(int m);
void CSR_free(ClosestStringResult * csr);
