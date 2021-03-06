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
