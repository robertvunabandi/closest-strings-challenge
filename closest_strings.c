/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#include <stdlib.h>

#include "./closest_strings.h"

ClosestStringResult *closest_string(
  char **words, 
  const int num_words, 
  const int m,
  int (*distance)(char *, char*, int)
) {
  return CSR_allocate(m);
}

// Allocating functions

ClosestStringResult *CSR_allocate(int m) {
  ClosestStringResult *csr = malloc(sizeof(ClosestStringResult));
  csr->s = malloc(sizeof(m * sizeof(char)));
  csr->m = m;
  csr->k = -1;
  return csr;
}

void CSR_deallocate(ClosestStringResult * csr) {
  free(csr->s);
  free(csr);
}
