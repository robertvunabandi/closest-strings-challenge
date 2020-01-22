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
 * Returns the hamming distance from the two strings `s1` and `s2`.
 * More specifically, it returns the number of positions at which
 * the corresponding characters are different.
 *
 * Preconditions:
 * - strnlen(s1) == strnlen(s2) == m
 */
int hammingDistance(char *s1, char *s2, int m);

/**
 * Returns the sum of the relative distances at each position of
 * the strings `s1` and `s2`. The relative distance is defined as
 * the number of characters in the alphabet it takes to go from
 * the lowerst appearing character to the highest appearing one.
 * For instance, relative distance from a to c is 2, from a to a
 * is 0, from c to a is also 2, from a to z is 26.
 *
 * Preconditions:
 * - strnlen(s1) == strnlen(s2) == m
 */
int relativeDistance(char *s1, char *s2, int m);

/**
 * This returns a distance that is almost the same as relative
 * distance except one can wrap around the alphabet. For instance,
 * the rotational relative distance from a to z is 1. In other words,
 * this returns the distance made from the shortest delta (either
 * moving back the alphabet or forward).
 *
 * Preconditions:
 * - strnlen(s1) == strnlen(s2) == m
 */
int rotRelativeDistance(char *s1, char *s2, int m);

/**
 * This returns a distance that works the following way. Given the words
 * s1 = {c1_1, c1_2, ..., c1_m} and s2 = {c2_1, c2_2, ..., c2_m}, returns
 * sum((|j - i| + 1) * hamming_distance(c1_i, c2_j)) for i, j in range [1..m].
 *
 * Preconditions:
 * - strnlen(s1) == strnlen(s2) == m
 */
int pairwiseHammingDistance(char *s1, char *s2, int m);
