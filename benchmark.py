#!/usr/local/bin/python3.8
import argparse
import json
import logging
import os
import random
import re
import subprocess
import sys
import tempfile
import traceback

from typing import List, Tuple

from py import utils as U


ALPHABET = list("abcdefghijklmnopqrstuvwxyz")
STYLE_SIMPLE = "SIMPLE"
STYLE_VARY = "VARY"
STYLE_RANDOM = "RANDOM"

##
## Data Type Definition(s)
##

# K and S as defined for `k` and `s` in the README.
CS_DistFunc = str
CS_TimeSec = float
CS_K = int
CS_S = str


class CSRunResult:
    # the number of lines it takes to output the result of one 
    # distance function is the following.
    SingleDistFuncResultLength = 6
    DistFunc_idx = 0
    DistFunc_label = "> Benchmarking "
    TimeSec_idx = 1
    TimeSec_label = "time: "
    K_idx = 3
    K_label = "k: "
    S_idx = 5
    S_label = "s: "
    METRICS = [
        (DistFunc_label, DistFunc_idx, CS_DistFunc), 
        (TimeSec_label, TimeSec_idx, CS_TimeSec),
        (K_label, K_idx, CS_K),
        (S_label, S_idx, CS_S),
    ]

    def __init__(self, run_stdout: str) -> None:
        lines = CSRunResult._remove_non_result_lines(run_stdout.splitlines())
        self._result_lines = lines
        self._results = self._extract_results()

    @staticmethod
    def _remove_non_result_lines(lines: List[str]) -> List[str]:
        first_idx = 0
        while not lines[first_idx].startswith("> Benchmarking"):
            first_idx += 1
        return lines[first_idx:]

    def _extract_results(self) -> List[Tuple[CS_DistFunc, CS_TimeSec, CS_K, CS_S]]:
        overall: List[Tuple[CS_DistFunc, CS_TimeSec, CS_K, CS_S]] = []
        for i in range(0, len(self._result_lines), CSRunResult.SingleDistFuncResultLength):
            result_lines = self._result_lines[i:(i + CSRunResult.SingleDistFuncResultLength)]
            result = []
            for metric_label, metric_idx, metric_type in CSRunResult.METRICS:
                line = result_lines[metric_idx].strip()
                metric_raw_value = line[len(metric_label):]
                metric_value = metric_type(metric_raw_value)
                result.append(metric_value)
            overall.append(tuple(result))
        # sort by distance_function name, which is at index 0
        return sorted(overall, key=lambda t: t[0])

##
## Functions
##

def make_words(num_words: int, num_letters: int, style: str) -> List[str]:
    if style == STYLE_SIMPLE:
        words = []
        char_index = 0
        for _ in range(num_words):
            words.append(ALPHABET[char_index] * num_letters)
            char_index = (char_index + 1) % len(ALPHABET)
        return words

    if style == STYLE_VARY:
        words = []
        char_index = 0
        current_word = ""
        while len(words) < num_words:
            current_word += ALPHABET[char_index]
            char_index = (char_index + 1) % len(ALPHABET)
            if len(current_word) == num_letters:
                words.append(current_word)
                current_word = ""
        return words

    if style == STYLE_RANDOM:
        words = []
        for _ in range(num_words):
            word = ""
            for _ in range(num_letters):
                word += ALPHABET[random.randint(0, len(ALPHABET) - 1)]
            words.append(word)
        return words
    
    raise ValueError(f"Style {style} is not yet implemented")


def extract_results_from_program_run(num_letters: int, words: List[str]) -> CSRunResult:
    # TODO - write this function
    raise NotImplementedError


##
## The Main Runner Program
##

EXIT_CODE_SUCCESS = 0
EXIT_CODE_FAILURE = 1
STARTING_NUM_LETTERS = 3


def run_benchmark(
    repeat: int, max_time: int, style: str, num_words: int, verbose: bool = False
) -> int:
    """
    Runs the `./cs` program multiple times with arguments, records the time
    the program took to run for each set of distance functions, and output
    the time the program took for various runs.

    This returns an exit code, which is EXIT_CODE_SUCCESS when everything
    runs without any error.
    """
    aggregated_max_time = None
    num_letters = STARTING_NUM_LETTERS
    output_columns: List[Tuple[str, ...]] = []
    while aggregated_max_time is None or aggregated_max_time < max_time:
        words = make_words(num_words, num_letters, style)
        program_results = [
            extract_results_from_program_run(num_letters, words) for _ in range(repeat)
        ]
    return EXIT_CODE_FAILURE 

##
## Defining the Parser
##

USAGE = """
"""
DEFAULT_REPEAT = 20
MIN_REPEAT = 1
DEFAULT_MAX_TIME_SEC = 60
MIN_TIME_SEC = 5
MIN_NUM_WORDS = 2


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=USAGE)
    parser.add_argument(
        "-r",
        "--repeat",
        default=DEFAULT_REPEAT,
        type=int,
        help=(
            "The number of times to run the program on a set of words to determine "
            f"roughly how long it takes to run. This is by default `{DEFAULT_REPEAT}`."
        ),
    )
    parser.add_argument(
        "-mt",
        "--max-time",
        default=DEFAULT_MAX_TIME_SEC,
        type=int,
        help=(
            "Don't move into the next set of words (i.e., increase length of `m` "
            "by 1) if the total time spent in the current set of words for any of "
            "the distance functions took more than this time when aggregated with "
            "the number of --repeat. This time is specified in seconds. This is by "
            f"default `{DEFAULT_MAX_TIME_SEC} and must be positive and at least "
            f"`{MIN_TIME_SEC}`."
        ),
    )
    parser.add_argument(
        "-s",
        "--style",
        default=STYLE_SIMPLE,
        type=str,
        choices=[STYLE_SIMPLE, STYLE_VARY, STYLE_RANDOM],
        help=(
            f"In the {STYLE_SIMPLE} style, each word will be composed of the "
            "same exact letters, with the first word being `aa...a` and the next "
            f"one being `bb...b`, and so on. In the {STYLE_VARY}, the first word "
            "will be `abcd...`, the next one will be wherever it left of and "
            "incrementaly continue this way. if we reach the end of the alphabet, "
            "words will start skipping by one more letter each time. In the "
            f"{STYLE_RANDOM}, each word is a random selections of letters."
        ),
    )
    parser.add_argument(
        "-nw",
        "--num-words",
        default=MIN_NUM_WORDS,
        type=int,
        choices=range(MIN_NUM_WORDS, len(ALPHABET)),
        metavar=f"[{MIN_NUM_WORDS}-{len(ALPHABET)}]",
        help=(
            f"The number of words to have. Must be in the range [{MIN_NUM_WORDS}, "
            f"{len(ALPHABET)}]."
        ),
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help=(
            "This will simply make the program print more things."
            # TODO: write what verbose truly does in the following vain.
            # "More specifically, the following events will be printed:"
        ),
    )
    args = parser.parse_args()

    print(U.in_cyan("== Benchmarking Current Closest String Program =="))

    repeat = args.repeat
    if repeat < MIN_REPEAT:
        print(U.in_yellow(
            f"-- Adjusting the repeat to {MIN_REPEAT} because what's "
            f"given ({repeat}) is invalid."
        ))
        repeat = MIN_REPEAT
    max_time = args.max_time
    if max_time < MIN_TIME_SEC:
        print(U.in_yellow(
            f"-- Adjusting the max_time to {MIN_TIME_SEC} because what's "
            f"given ({max_time}) is invalid."
        ))
        max_time = MIN_TIME_SEC
    style = args.style
    num_words = args.num_words
    verbose = args.verbose

    print(args)
    sys.exit(run_benchmark(repeat, max_time, style, num_words, verbose=verbose))
