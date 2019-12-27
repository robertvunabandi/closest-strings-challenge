/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include "./closest_strings.h"

#include "./alphabet.h"
#include "./util.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//
// Defining things to help with the current algorithm and creating
// forward references not defined in the header.
//

/**
 * Finds the next word in an arbitrary order of words given the
 * current word. This next word is set inside wordOutput. wordOutput
 * may be the same pointer as currentWord. This will return true
 * whenever the next word outputted is valid and false otherwise.
 *
 * Words are ordered such that if a < b, then in order to get the b,
 * we need to call nextWord(...(nextWord(a))) enough time such that
 * we get to b eventually.
 *
 * Precondition:
 * - currentWord is lowercase alphanumeric.
 * - There is a strict order. If nextWord(a) = b and nextWord(b) = c,
 *   then a < b and b < c. This order is also transitive.
 * Postcondition:
 * - There is a maximum word we get from calling getMaxWord(length). If
 *   currentWord is the maxWord, this will return false. Otherwise, it
 *   will always return the next word.
 */
bool setNextWord(char *currentWord, int length, char *wordOutput);
void setMinWord(int length, char *wordOutput);
void setMaxWord(int length, char *wordOutput);

//
// Main function: closest_string
//

void closest_string(
  char **words,
  const int num_words,
  const int m,
  int (*distance)(char *, char *, int),
  ClosestStringResult *csr
) {
  assert(csr->k == -1);

  // very naive approach: for every possible word of length m
  // find k for that letter. if this k is smaller than the best
  // we have, pick it as the best.
  char *word = malloc(m * sizeof(char));
  char *maxWord = malloc(m * sizeof(char));
  setMinWord(m, word);
  setMaxWord(m, maxWord);
  while (true) {
    // compute k and then update csr->k if this is a better k.
    int max_k = -1;
    for (int i = 0; i < num_words; i++) {
      int dist = distance(word, words[i], m);
      if (dist > max_k) {
        max_k = dist;
      }
    }
    assert(max_k > -1);
    if (csr->k == -1 || max_k < csr->k) {
      csr->k = max_k;
      strcpy(csr->s, word);
    }

    // move onto the next word if it's valid.
    bool valid = setNextWord(word, m, word);
    if (!valid) {
      break;
    }
  }
  free(word);
  free(maxWord);
}

//
// Definitions of forward references
//

// Increment the character at index and returns true if we need to
// carry over.
bool incrementCharacter(char *word, int index) {
  char character = word[index];
  if (character == ALPHABET[ALPHABET_LENGTH - 1]) {
    word[index] = ALPHABET[0];
    return true;
  }
  for (int i = 0; i < ALPHABET_LENGTH; i++) {
    if (character == ALPHABET[i]) {
      word[index] = ALPHABET[i + 1];
      return false;
    }
  }
  // Shouldn't get here.
  assert(false);
  return false;
}

bool setNextWord(char *currentWord, int length, char *wordOutput) {
  // If this is the max word, we want to return false.
  char *maxWord = malloc(length * sizeof(char));
  setMaxWord(length, maxWord);
  if (String_equal(currentWord, maxWord)) {
    free(maxWord);
    return false;
  }
  char *word = maxWord;
  strcpy(word, currentWord);

  int index = 0;
  while (true) {
    bool should_carry = incrementCharacter(word, index);
    if (!should_carry) {
      break;
    }
    index++;
    assert(index < length);
  }
  strcpy(wordOutput, word);
  free(word);
  return true;
}

void setMinWord(int length, char *wordOutput) {
  for (int i = 0; i < length; i++) {
    wordOutput[i] = ALPHABET[0];
  }
}

void setMaxWord(int length, char *wordOutput) {
  for (int i = 0; i < length; i++) {
    wordOutput[i] = ALPHABET[ALPHABET_LENGTH - 1];
  }
}

//
// Allocating functions
//

ClosestStringResult *CSR_allocate(int m) {
  ClosestStringResult *csr = malloc(sizeof(ClosestStringResult));
  csr->s = malloc(sizeof(m * sizeof(char)));
  csr->m = m;
  csr->k = -1;
  return csr;
}

void CSR_free(ClosestStringResult *csr) {
  free(csr->s);
  free(csr);
}
