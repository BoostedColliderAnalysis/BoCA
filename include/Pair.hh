/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#define OBSERVABLE_1(value) boca::Observable(value, #value, #value)
#define OBSERVABLE_2(value, string) boca::Observable(value, #value, string)

#define ARGUMENTS(arg1, arg2, arg, ...) arg
#define OBSERVABLE_CHOOSE(...) ARGUMENTS(__VA_ARGS__, OBSERVABLE_2, OBSERVABLE_1, )

#define OBSERVABLE(...) OBSERVABLE_CHOOSE(__VA_ARGS__)(__VA_ARGS__)
