/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <algorithm>

namespace analysis
{

/**
 * @brief Calcualte distance in eta phi space
 *
 */
float Distance(float rapidity_1, float phi_1, float rapidity_2, float phi_2);

/**
 * @brief Calcualte distance from center in eta phi space
 *
 */
float Length(float rapidity, float phi);

/**
 * @brief Take care of phi angles around pi
 *
 */
float DeltaPhi(float phi_1, float phi_2);

float RestrictPhi(float phi);

template <typename Value>
/**
 * @brief derives the sign of the value
 *
 */
int sgn(Value value)
{
    return (Value(0) < value) - (value < Value(0));
}

template <typename Value>
/**
 * @brief derives the square of the value
 *
 */
Value sqr(Value value)
{
    return value * value;
}

template <typename Value>
int Closest(std::vector<Value> const& vector, Value value)
{
    auto position = std::lower_bound(vector.begin(), vector.end(), value, [](float a, float b) {
        return a > b;
    });
    if (position == vector.end()) return 0;
    return position - vector.begin();
}

int LargeNumber();

float RoundError(float value);

float RoundToDigits(float value, int digits = 3);

float RoundToError(float value, float error);

float FloorToDigits(float value, int digits = 2);

float CeilToDigits(float value, int digits = 2);

}
