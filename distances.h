/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
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
