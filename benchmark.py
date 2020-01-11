#!/usr/local/bin/python3.8
import argparse
import random
import subprocess
import sys

from typing import Dict, List, Tuple, Union

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
                if metric_label == CSRunResult.TimeSec_label or metric_label == CSRunResult.DistFunc_label:
                    metric_raw_value = metric_raw_value[:-1]
                metric_value = metric_type(metric_raw_value)
                result.append(metric_value)
            overall.append(tuple(result))
        # sort by distance_function name, which is at index 0
        return sorted(overall, key=lambda t: t[0])

    def __iter__(self):
        for (dist_func, time_sec, k, s) in self._results:
            yield (dist_func, time_sec, k, s)


METRIC_AVG = "avg"
DECIMAL_PLACES = 5

class MetricValues:
    def __init__(self, values: List[Union[int, float]]) -> None:
        self.avg = self.compute_average(values)
        self.tot = sum(values)

    def get_metric(self, metric_name: str) -> None:
        if metric_name == METRIC_AVG:
            return round(self.avg, DECIMAL_PLACES)

        raise ValueError(f"metric {metric_name} is not yet implemented")

    @staticmethod
    def compute_average(values: List[Union[int, float]]) -> float:
        return sum(values) / len(values)

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
    try:
        result = subprocess.run(
            ["./cs", "-l", str(num_letters), "-w", *words],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL
        )
    except subprocess.CalledProcessError as cpe:
        print(U.in_red(cpe))
        sys.exit(EXIT_CODE_FAILURE)
    return CSRunResult(result.stdout.decode())


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
    aggregated_max_time = -1 
    num_letters = STARTING_NUM_LETTERS
    v_nl = "\n" if verbose else ""
    # run the program until we exceed the max time required. If any run exceeds
    # the max time, then we will automatically stop. We will collect them in 
    # this dictionary that maps num_letters to a dictionary that maps distance
    # function to MetricValues.
    overall_results: Dict[int, Dict[str, MetricValues]] = {}
    while aggregated_max_time == -1 or aggregated_max_time < max_time:
        aggregated_max_time = 0
        words = make_words(num_words, num_letters, style)
        result_for_dist_function: Dict[int, List[Union[int, float]]] = {}
        should_break = False
        print(f"{v_nl}NOW USING {num_letters} LETTER WORDS:{v_nl}")
        for run_round in range(repeat):
            if verbose:
                program_args = f"`./cs -l {num_letters} -w {' '.join(words)}`"
                print(f"  running {program_args} (round {run_round + 1}/{repeat})")
            results: CSRunResult = extract_results_from_program_run(num_letters, words)
            for dist_function, time, _, _ in results:
                if time > max_time:
                    should_break = True
                    break
                result_for_dist_function.setdefault(dist_function, []).append(time)
            if should_break:
                break
        if should_break:
            print("  ...aborting because a run took more than the maximum allowed time...")
            break
        overall_results[num_letters] = {}
        for dist_func, times in result_for_dist_function.items():
            overall_results[num_letters][dist_func] = MetricValues(times)
            aggregated_max_time = max(aggregated_max_time, overall_results[num_letters][dist_func].tot)
        num_letters += 1
    # Now, print the results out.
    print("\nOUTPUTING RESULTS:\n")
    # metrics are actual fields in MetricValues.
    metrics = [METRIC_AVG]
    # grab the distance functions from the first key's value in 
    # `overall_results` (there should be at least one key)
    dist_functions = [dist_func for dist_func in overall_results[next(iter(overall_results))]]
    rows = [["num_letters"]]
    row_idx_map: Dict[str, Dict[str, int]] = {}
    for df in dist_functions:
        for m in metrics:
            row_idx_map.setdefault(df, {})[m] = len(rows)
            v = f"{df}.{m}"
            rows.append([v])
    for num_letters in sorted(overall_results):
        rows[0].append(str(num_letters))
        for distance_func in overall_results[num_letters]:
            metric_values = overall_results[num_letters][distance_func]
            for metric in metrics:
                idx = row_idx_map[distance_func][metric]
                rows[idx].append(str(metric_values.get_metric(metric)))
    for row in rows:
        print(" ".join(row))
    return EXIT_CODE_SUCCESS 

##
## Defining the Parser
##

USAGE = """
Runs the `./cs` program with the given arguments and outputs a table result
for how long the program took with each number of letters. The final output
is a space-separated table where the values of the first row are the 
number of letter and the values of the rest of the rows are the average
times the program took to run. This can be easily pasted into Google Sheets
for nicer UI. See README for more details on the final output. NOTE: make 
sure to run `make` before running this script.
"""
DEFAULT_REPEAT = 20
MIN_REPEAT = 1
DEFAULT_MAX_TIME_SEC = 60
MIN_TIME_SEC = 1
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
            f"{len(ALPHABET)}]. This is be default `{MIN_NUM_WORDS}`."
        ),
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help=(
            "This will simply make the program print more things. "
            "More specifically, each time the ./cs program actually runs, "
            "it will print out the arguments it's running with."
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
    max_time = round(max_time)
    style = args.style
    num_words = args.num_words
    verbose = args.verbose

    # print out the arguments
    print("\nPROGRAM ARGUMENTS:\n")
    print(f"  Maximum Time: {max_time} second{'s' if max_time > 1 else ''}")
    print(f"  Style: {style}")
    print(f"  Number of Words: {num_words}")
    print(f"  Verbosity: {str(verbose).lower()}")
    # just for printing and consistent printing purposes...
    if not verbose:
        print()
    sys.exit(run_benchmark(repeat, max_time, style, num_words, verbose=verbose))
