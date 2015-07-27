#pragma once

#define PAIR1(value) Obs(value, #value, #value)
#define PAIR2(value, string) Obs(value, #value, string)

#define ARGUMENTS(arg1, arg2, arg, ...) arg
#define PAIRCHOOSER(...) ARGUMENTS(__VA_ARGS__, PAIR2, PAIR1, )

#define PAIR(...) PAIRCHOOSER(__VA_ARGS__)(__VA_ARGS__)
