/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include "./distances.h"

#include "./alphabet.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

//
// First, defining functions to be used by the API functions in distance.h
//

/**
 * A data structure to hold two characters in sorted order using the
 * ALPHABET defined in `alphabet.h` for ordering.
 * 
 * Invariants:
 * - Both `first` and `second` appear in the ALPHABET
 * - `first` appears before or in the same place as `second` in the ALPHABET
 * - `second` appears after or in the same place as `first` in the ALPHABET
 */
typedef struct SortedChar {
  char first;
  char second;
} SortedChar;

/**
 * This method is very self explanatory.
 *
 * Precondition:
 * - s1 and s2 are in ALPHABET (i.e., lowercase alphanumeric)
 */
SortedChar getSortedChar(char s1, char s2) {
  // Time Complexity: ALPHABET_LENGTH
  char first = '\0';
  char second = '\0';
#ifdef DEBUG
  bool broke = false;
#endif
  for (int i = 0; i < ALPHABET_LENGTH; i++) {
    if (s1 == ALPHABET[i]) {
      first = s1;
      second = s2;
#ifdef DEBUG
      broke = true;
#endif
      break;
    }
    if (s2 == ALPHABET[i]) {
      first = s2;
      second = s1;
#ifdef DEBUG
      broke = true;
#endif
      break;
    }
  }
#ifdef DEBUG
  assert(broke);
#endif
  return (SortedChar) {.first = first, .second = second};
}

/**
 * This computes the number of letters it takes to go from `first` to `second` 
 * in the alphabet. In case second appears before first in the alphabet, it 
 * will wrap around and compute the distance from `first` to "z" + 1 + distance 
 * from "a" to `second`. Each character counts as 1.
 */
int relativeCharDistance(char first, char second) {
  // Time Complexity: WRAPPED_ALPHABET_LENGTH
  int firstIdx = -1;
  int secondIdx = -1;

  for (int i = 0; i < WRAPPED_ALPHABET_LENGTH; i++) {
    if (firstIdx == -1) {
      assert(secondIdx == -1);
      if (first == ALPHABET[i]) {
        firstIdx = i;
        if (second == ALPHABET[i]) {
          secondIdx = i;
          break;
        }
      }
      continue;
    }

    assert(secondIdx == -1);
    if (second == ALPHABET[i]) {
      secondIdx = i;
      break;
    }
  }

  assert(firstIdx != -1);
  assert(secondIdx != -1);
  int result = secondIdx - firstIdx;
  assert(result >= 0);
  return result;
}

//
// Definitions for the API in distance.h
//

int hammingDistance(char *s1, char *s2, int m) {
  // Time Complexity: m
  int result = 0;
  for (int i = 0; i < m; i++) {
    if (s1[i] != s2[i]) {
      result += 1;
    }
  }
  return result;
}

int relativeDistance(char *s1, char *s2, int m) {
  // Time Complexity: m * (getSortedChar + relativeCharDIstance)
  int result = 0;
  for (int i = 0; i < m; i++) {
    SortedChar sc = getSortedChar(s1[i], s2[i]);
    result += relativeCharDistance(sc.first, sc.second);
  }
  return result;
}

int rotRelativeDistance(char *s1, char *s2, int m) {
  // Time Complexity: 2 * m * relativeCharDistance
  int result = 0;
  for (int i = 0; i < m; i++) {
    int foward = relativeCharDistance(s1[i], s2[i]);
    int backward = relativeCharDistance(s2[i], s1[i]);
    result += foward < backward ? foward : backward;
  }
  return result;
}

int pairwiseHammingDistance(char *s1, char *s2, int m) {
  int result = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (s1[i] != s2[j]) {
        result += abs(j - i) + 1;
      }
    }
  }
  return result;
}
