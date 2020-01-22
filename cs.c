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

#include "./cs.h"

#include "./closest_strings.h"
#include "./colors.h"
#include "./distances.h"
#include "./util.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//
// Allocating the List of Words
//

char **allocate_words(int argc, const int m) {
  // Make an array that is sufficiently large to fit all the
  // words of size m. There shouldn't be more words than the
  // total number of arguments. All words should be of the
  // same size m, and each word is simply a sequence of
  // alphabetical characters.
  char **words = malloc(argc * sizeof(char *));
  for (int i = 0; i < argc; i++) {
    words[i] = malloc(m * sizeof(char));
  }
  return words;
}

void free_words(char **words, int argc) {
  for (int i = 0; i < argc; i++) {
    free(words[i]);
  }
  free(words);
}

//
// Parsing Program Arguments
//

const char *USAGE = "usage: ./cs [-l LENGTH] -w WORD [WORD ...]";
const char *TITLE_SPACE = "  ";
const char *DESCR_SPACE = "    ";
// Required arguments
const char *W_FLAG_TITLE = "-w WORD [WORD ...], --words WORD [WORD ...]";
const char *W_FLAG_DESCR = "the words to find the closest string of";
// Optional arguments
const char *H_FLAG_TITLE = "-h, --help";
const char *H_FLAG_DESCR = "show this help message and exit";
const char *L_FLAG_TITLE = "-l LENGTH, --length LENGTH";
const char *L_FLAG_DESCR = "this is how long each word is going to be";

/**
 * @param argc - number of arguments given
 * @param argv - an array of length argc of arguments given to the program
 * @return true if the `-h` or `--help` flag appears in argv, false otherwise
 */
bool hasHelpFlag(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    char *flag = argv[i];
    if (String_equal(flag, "-h") || String_equal(flag, "--help")) {
      return true;
    }
  }
  return false;
}

void displayHelp() {
  printf("%s\n\n", USAGE);
  printf(
    "This program measures how fast the closest distance function runs "
    "against the given sets of words with the given word length.\n\n"
  );
  printf(
    "required arguments:\n%s%s\n%s%s\n\n",
    TITLE_SPACE, W_FLAG_TITLE,
    DESCR_SPACE, W_FLAG_DESCR
  );
  printf(
    "optional arguments:\n%s%s\n%s%s\n%s%s\n%s%s\n",
    TITLE_SPACE, H_FLAG_TITLE,
    DESCR_SPACE, H_FLAG_DESCR,
    TITLE_SPACE, L_FLAG_TITLE,
    DESCR_SPACE, L_FLAG_DESCR
  );
}

/**
 * @param argc - number of arguments given
 * @param argv - an array of length argc of arguments given to the program
 * @return the value of the flag `-l` or `--length` if passed in,
 *         DEFAULT_M if not passed in, and `-1` if the value of the
 *         flag was invalid. It must be a positive, non-zero integer.
 */
int getMValue(int argc, char **argv) {
  // start at 1 because index 0 is the program `./cs` itself
  int m_idx = 1;
  int length = DEFAULT_M;
  while (m_idx < argc) {
    char *flag = argv[m_idx];
    if (String_equal(flag, "-l") || String_equal(flag, "--length")) {
      if (m_idx == argc - 1) {
        fprintf(
          stderr,
          (
            "Error: Received length flag `%s`, but no argument "
            "value for length given.\n"
          ),
          flag 
        );
        return -1;
      }
      char *length_value = argv[m_idx + 1];
      length = atoi(length_value);
      if (length == 0) {
        fprintf(
          stderr, 
          "Error: Invalid argument value for length. Got `%s`\n", 
          length_value
        );
        return -1;
      }
      return length;
    }

    m_idx++;
  }
  return length;
}

bool is_word_valid(char *word, int m) {
  // word must have the right length.
  if (strlen(word) != m) {
    fprintf(
      stderr,
      (
        "Error: The given word `%s` is invalid because it "
        "doesn't have length %d.\n"
      ),
      word, 
      m
    );
    return false;
  }

  // word must only contain alphabetical letters
  for (int i = 0; i < m; i++) {
    if (!isalpha(word[i])) {
      fprintf(
        stderr,
        (
          "Error: The given word `%s` is invalid because "
          "it contains non-alphabetical characters.\n"
        ),
        word
      );
      return false;
    }
    // convert to make this easier to work with.
    word[i] = tolower(word[i]);
  }
  return true;
}

/**
 * @param output - the array of memory in which to put the words given in
 *                 argv.
 * @param m - how long each words are going to be. See README.
 * @param argc - number of arguments given
 * @param argv - an array of length argc of arguments given to the program.
 *               the flag `-w` or `--words` must be given, and it must be
 *               followed by at least one word of length m. This flag cannot
 *               be passed in twice.
 * @return The number of words from argv added to output, or `-1` if there
 *         was an error while validating the words or if no words were given.
 */
int getWords(char **output, const int m, int argc, char **argv) {
  int words_found = 0;
  int w_flag_idx = 1;
  bool inside_w_flag = false;

  while (w_flag_idx < argc) {
    if (!inside_w_flag) {
      char *flag = argv[w_flag_idx];
      if (String_equal(flag, "-w") || String_equal(flag, "--words")) {
        inside_w_flag = true;
      }
      w_flag_idx++;
      continue;
    }
    // now, we're inside the -w flag.
    char *pot_word = argv[w_flag_idx];
    // if we encounter another flag, we're done looking.
    if (pot_word[0] == '-') {
      inside_w_flag = false;
      break;
    }
    if (!is_word_valid(pot_word, m)) {
      return -1;
    }

    strncpy(output[words_found++], pot_word, m);
    w_flag_idx++;
  }
  if (words_found == 0) {
    fprintf(stderr, "Error: No words given.\n");
    return -1;
  }
  return words_found;
}

/**
 * Runs the `closest_strings` program defined in `closest_strings.h`
 * with the given words and then report how long it took to run.
 *
 * @param words - words given in the CLI
 * @param num_words - total number of words
 * @param m - the length of each words. All words must have this length.
 * @param distance - a function that computes the distance of two words
 *                   that have the same length
 * @param info - A string to print when running this benchmark
 */
void runBenchmark(
  char **words,
  const int num_words,
  const int m,
  int (*distance)(char *, char *, int),
  char *info
) {
  struct timespec t_start, t_end;
  ClosestStringResult *csr = CSR_allocate(m);
  printf("> Benchmarking %s:\n", info);

  clock_gettime(CLOCK_MONOTONIC, &t_start);
  closest_string(words, num_words, m, distance, csr);
  clock_gettime(CLOCK_MONOTONIC, &t_end);
  report_time(&t_start, &t_end, "    ");
  printf("    results:\n");
  printf("      k: %d\n", csr->k);
  printf("      m: %d\n", csr->m);
  printf("      s: %s\n", csr->s);

  CSR_free(csr);
}

/**
 * The main function. This takes in the program arguments and runs them
 * as specified. Run with flags `--help` for information on how to run
 * this.
 *
 * @param argc - number of arguments given
 * @param argv - an array of length argc of arguments given to the program.
 *               the flag `-w` or `--words` must be given, and it must be
 *               followed by at least one word of length m. This flag cannot
 *               be passed in twice.
 */
int main(int argc, char **argv) {
  // Check to see if the help flag was given and display help
  // and exit if given.
  if (hasHelpFlag(argc, argv)) {
    displayHelp();
    exit(0);
  }

  // Read and interpret the command line arguments.
  printf("%s== RUNNING CLOSEST STRING PROGRAM ==%s\n\n", C_BOLD_CYAN, C_NC);

  // TODO(enhancement): Prevent invalid flags and double flags

  const int m = getMValue(argc, argv);
  if (m == -1) {
    fprintf(stderr, "%s\n", USAGE);
    exit(1);
  }

  char **words = allocate_words(argc, m);
  int num_words = getWords(words, m, argc, argv);
  if (num_words == -1) {
    fprintf(stderr, "%s\n", USAGE);
    free_words(words, argc);
    exit(1);
  }

  // Pring the program's arguments.
  printf("M:         %s%d%s\n", C_BOLD_WHITE, m, C_NC);
  printf("num_words: %s%d%s\n", C_BOLD_WHITE, num_words, C_NC);
  printf("words:     %s{", C_BOLD_WHITE);
  for (int i = 0; i < num_words - 1; i++) {
    printf("%s, ", words[i]);
  }
  printf("%s}%s\n\n", words[num_words - 1], C_NC);

  // Start running the program, timing each specific distance
  // functions.
  runBenchmark(words, num_words, m, &hammingDistance, "hammingDistance");
  runBenchmark(words, num_words, m, &relativeDistance, "relativeDistance");
  runBenchmark(words, num_words, m, &rotRelativeDistance, "rotRelativeDistance");
  runBenchmark(words, num_words, m, &pairwiseHammingDistance, "pairwiseHammingDistance");

  free_words(words, argc);
  return 0;
}
