/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#pragma once

// This is how long our words are going to be by default.
#define DEFAULT_M 8

typedef struct CSResult {
    int distance_sum;
    int word_length;
    char * word;
} CSResult;