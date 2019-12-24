/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include <assert.h>
#include <stdbool.h>

#include "./distances.h"

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

const char *ALPHABET = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
const int ALPHABET_LENGTH = 26;
const int WRAPPED_ALPHABET_LENGTH = ALPHABET_LENGTH * 2;
typedef struct SortedChar {
  char first;  // this appears before or same as `second` in the alphabet
  char second; // this appears same or after `first` in the alphabet
} SortedChar;  // NOTE: these are for length up to ALPHABET_LENGTH
SortedChar getSortedChar(char s1, char s2);
int relativeCharDistance(char first, char second);

int relativeDistance(char *s1, char *s2, int m) {
  // Time Complexity: m * (getSortedChar + relativeCharDIstance)
  int result = 0;
  for (int i = 0; i < m; i++) {
    SortedChar sc = getSortedChar(s1[i], s2[i]);
    result += relativeCharDistance(sc.first, sc.second);
  }
  return result;
}

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
# ifdef DEBUG
  bool broke = false;
# endif
  for (int i = 0; i < ALPHABET_LENGTH; i++) {
    if (s1 == ALPHABET[i]) {
      first = s1;
      second = s2;
# ifdef DEBUG
      broke = true;
# endif
      break;
    }
    if (s2 == ALPHABET[i]) {
      first = s2;
      second = s1;
# ifdef DEBUG
      broke = true;
# endif
      break;
    }
  }
# ifdef DEBUG
  assert(broke);
# endif
  return (SortedChar) {.first=first, .second=second};
}

int rotRelativeDistance(char *s1, char *s2, int m) {
  // Time Complexity: 2 * m * relativeCharDistance
  int result = 0;
  // TODO: implement this function
  for (int i = 0; i < m; i++) {
    int foward = relativeCharDistance(s1[i], s2[i]);
    int backward = relativeCharDistance(s2[i], s1[i]);
    result += foward < backward ? foward : backward;
  }
  return result;
}

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

