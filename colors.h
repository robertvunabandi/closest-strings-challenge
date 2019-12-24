/**
 * Copyright (c) 2019-2020 Robert M. Vunabandi
 */

#pragma once

// Colors for nice prints. Found many of these colors from these links:
// https://stackoverflow.com/questions/1961209/making-some-text-in-printf-appear-in-green-and-red
// http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
// Regular Colors
#define C_RED ("\033[31m")     /* Red */
#define C_BLUE ("\033[34m")    /* Blue */
#define C_CYAN ("\033[36m")    /* Cyan */
#define C_BLACK ("\033[30m")   /* Black */
#define C_GREEN ("\033[32m")   /* Green */
#define C_WHITE ("\033[37m")   /* White */
#define C_YELLOW ("\033[33m")  /* Yellow */
#define C_MAGENTA ("\033[35m") /* Magenta */
// Bold Colors
#define C_BOLD_BLACK ("\033[1m\033[30m")   /* Bold Black */
#define C_BOLD_RED ("\033[1m\033[31m")     /* Bold Red */
#define C_BOLD_GREEN ("\033[1m\033[32m")   /* Bold Green */
#define C_BOLD_YELLOW ("\033[1m\033[33m")  /* Bold Yellow */
#define C_BOLD_BLUE ("\033[1m\033[34m")    /* Bold Blue */
#define C_BOLD_MAGENTA ("\033[1m\033[35m") /* Bold Magenta */
#define C_BOLD_CYAN ("\033[1m\033[36m")    /* Bold Cyan */
#define C_BOLD_WHITE ("\033[1m\033[37m")   /* Bold White */
// Background Colors
#define C_BKG_RED ("\033[41m")     /* Background Red */
#define C_BKG_BLUE ("\033[44m")    /* Background Blue */
#define C_BKG_CYAN ("\033[46m")    /* Background Cyan */
#define C_BKG_BLACK ("\033[40m")   /* Background Black */
#define C_BKG_GREEN ("\033[42m")   /* Background Green */
#define C_BKG_WHITE ("\033[47m")   /* Background White */
#define C_BKG_YELLOW ("\033[43m")  /* Background Yellow */
#define C_BKG_MAGENTA ("\033[45m") /* Background Magenta */
// Reset Color
#define C_NC ("\033[0m")
