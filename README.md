# README

This is `C` code that runs a program to solve the [Closest Strings](https://en.wikipedia.org/wiki/Closest_string)
problem. The purpose of writing this program is simply to have fun
optmizing this simple program as much as possible. 

## Closest Strings

For this code, we will use this following formal definition of the problem.

Given `N` length `M` strings `S={s_1, s_2, ..., s_N}` and given a distance 
function `distance` that takes two strings of length `M` as arguments and
returns an integer distance of the two string arguments, find the integer `k` 
and any new length-`M` string `s` such that `distance(s_i, s) <= k` where 
`k` is the smallest possible `k` for all `i` in range `[1..n]`. 

How can we prove that this is correct? Check that for every possible length-`M` 
string `s'`, `distance(s_i, s) <= distance(s_i, s')`. In other words, there 
doesn't exist any other string in the set of all possible strings of length `M`
that has a distance smaller than the one given by `s`.

The way this problem is formulated above should still be [W\[1\]-Hard](https://en.wikipedia.org/wiki/Parameterized_complexity#W_hierarchy) because to answer
the question of whether there exists an integer `k'` for which there exists a 
length-`M` string `s` such that the `distance(s_i, s) <= k'` could be answered
by solving for the smallest `k` and returning the boolean `k' >= k`. In fact,
the way we solve it solves a harder problem, which is to find the smallest `k`.
So, it may be more difficult.

## Running this Program

## Benchmarking

To benchmark this script, simply run the `benchmark.py` script.

The final output of running the program with the arguments 
`./benchmark.py -m 1 -r 20 -v` may look like the following:

```
num_letters 3 4
hammingDistance.avg 0.00184 0.0467
pairwiseHammingDistance.avg 0.00207 0.06047
relativeDistance.avg 0.0031 0.08844
rotRelativeDistance.avg 0.00545 0.16162
```

By default, the number of words is `2`, and the style is `SIMPLE` (run 
`./benchmark --help` for more details). So, looking at the cell in the second 
row and second column, it means that that the average time to find the closest 
string with the `hammingDistance` distance function of the words `aaa` and `bbb` 
is `0.00184` seconds (average after running the program 20 times). Similarly, 
using the `relativeDistance` distance function with length 4 words `aaaa` and 
`bbbb` takes `0.08844` seconds on average for 20 runs.

**NOTE:** This script uses some non-backward compatible features of Python 3.8, 
so you will need to run it with [Python 3.8](https://www.python.org/downloads/release/python-380/).

### Pasting Into Google Sheets

The final output of this benchmarking script is meant to be easily pastable 
into Google Sheets. This is so that one can keep track of various times and 
actually be able to compare different optimizations that they've made over time.
To do so, simply do the following:

1. Copy the final output
  ![Step 1](./assets/step-1)
2. Paste it into Google Sheets, click on the drop down, and select "Split text to columns"
  ![Step 2](./assets/step-2)
3. Click on the "separator" dropdown, and choose "Space"
  ![Step 3](./assets/step-3)
4. The final output should look like this:
  ![Step 4](./assets/step-4)
