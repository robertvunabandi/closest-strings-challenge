# README

This is `C` code that runs a program to solve the [Closest Strings](https://en.wikipedia.org/wiki/Closest_string)
problem. The purpose of writing this program is simply to have fun
optmizing this simple program as much as possible. 

## Closest Strings

For this code, we will use this following formal definition of the problem.

Given `N` length `M` strings `S={s_1, s_2, ..., s_N}` and given a distance 
function `distance` that takes two strings of length `M` as arguments and
returns an integer distance of the two string arguments, find a new string
`s` such that `sum(distance(s_i, s)) <= sum(distance(s_i, s'))` for all 
possible strings `s'` for `i` in range `[1..n]`. In other words, find 
another string of length `M` that minimizes the total distance from the
strings in the set `S`.

## Running this Program