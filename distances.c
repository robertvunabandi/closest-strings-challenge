/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include <assert.h>
#include <stdbool.h>

#include "./distances.h"

int hammingDistance(char *s1, char *s2, int m) {
  int result = 0;
  for (int i = 0; i < m; i++) {
    if (s1[i] != s2[i]) {
      result += 1;
    }
  }
  return result;
}

const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const int ALPHABET_LENGTH = 26;

int relativeDistance(char *s1, char *s2, int m) {
  int result = 0;
  for (int i = 0; i < m; i++) {
    bool started = false;
    bool broke = false;
    int count = 0;
    char first;
    char second;

    for (int j = 0; j < ALPHABET_LENGTH; j++) {
      // first, figure out which character came first
      if (!started) {
        if (s1[j] == ALPHABET[j]) {
          first = s1[j];
          second = s2[j];
        } else if (s2[j] == ALPHABET[j]) {
          first = s2[j];
          second = s1[j];
        } else {
          continue;
        }
      }
      // if we found the second character, stop
      if (second == ALPHABET[j]) {
        broke = true;
        break;
      }
      // increment the count each time until we find the
      // second character.
      count++;
    }

    // we must always break because one must come after the other
    assert(broke);
    result += count;
  }
  return result;
}

int rotRelativeDistance(char *s1, char *s2, int m) {
  int result = 0;
  // TODO: implement this function
  for (int i = 0; i < m; i++) {
    // int started = false;
    // char first;
    // char second;
  }
  return result;
}
