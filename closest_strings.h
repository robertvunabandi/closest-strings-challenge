/**
 * copyright (c) 2020 robert m. vunabandi
 * 
 * permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "software"), to deal
 * in the software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the software, and to permit persons to whom the software is
 * furnished to do so, subject to the following conditions:
 * 
 * the above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the software.
 * 
 * the software is provided "as is", without warranty of any kind, express or
 * implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose and noninfringement. in no event shall the
 * authors or copyright holders be liable for any claim, damages or other
 * liability, whether in an action of contract, tort or otherwise, arising from,
 * out of or in connection with the software or the use or other dealings in
 * the software.
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
 * - distance is symmetric: distance(s1, s2, m) = distance(s2, s1, m)
 *
 * Postcondition (result placed inside `csr`):
 * If `r` is the result of this call, then :
 * - distance(r->s, word, m) <= r->k for all `word` in `words`
 * - for all other length-`m` string `s`, there does not exist `word` in `words`
 *   such that distance(s, word, m) < r->k
 *
 * NOTE:
 * Outside of the symmetry property nothing else can be assumed about the way
 * the distance function works. In other words, one cannot assume that it
 * computes the distance by summing up the distances of each character
 * against each other.
 */
void closest_string(
  char **words,
  const int num_words,
  const int m,
  int (*distance)(char *, char *, int),
  ClosestStringResult *csr
);

// Allocating ClosestStringResult functions

ClosestStringResult *CSR_allocate(int m);
void CSR_free(ClosestStringResult *csr);
