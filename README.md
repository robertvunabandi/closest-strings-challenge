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
