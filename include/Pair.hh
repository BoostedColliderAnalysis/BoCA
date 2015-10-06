/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#define PAIR1(value) boca::Obs(value, #value, #value)
#define PAIR2(value, string) boca::Obs(value, #value, string)

#define ARGUMENTS(arg1, arg2, arg, ...) arg
#define PAIRCHOOSE(...) ARGUMENTS(__VA_ARGS__, PAIR2, PAIR1, )

#define PAIR(...) PAIRCHOOSE(__VA_ARGS__)(__VA_ARGS__)
