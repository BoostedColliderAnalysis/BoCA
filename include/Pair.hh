#pragma once

#define PAIR1(value) ::analysis::Obs(value, #value, #value)
#define PAIR2(value, string) ::analysis::Obs(value, #value, string)

#define ARGUMENTS(arg1, arg2, arg, ...) arg
#define PAIRCHOOSE(...) ARGUMENTS(__VA_ARGS__, PAIR2, PAIR1, )

#define PAIR(...) PAIRCHOOSE(__VA_ARGS__)(__VA_ARGS__)
