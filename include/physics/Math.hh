/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <algorithm>
#include <boost/range/algorithm/lower_bound.hpp>
#include <boost/range/algorithm/upper_bound.hpp>

namespace boca
{

/**
 * @brief derives the sign of the value
 *
 */
template <typename Value>
int sgn(Value value)
{
    return (Value(0) < value) - (value < Value(0));
}

template <typename Value>
int LowerBound(std::vector<Value> const& vector, Value value)
{
    auto position = boost::range::lower_bound(vector, value, [](float a, float b) {
        return a > b;
    });
    if (position == vector.end()) return 0;
    return position - vector.begin();
}

template <typename Value>
int UpperBound(std::vector<Value> const& vector, Value value)
{
    auto position = boost::range::upper_bound(vector, value, [](float a, float b) {
        return a > b;
    });
    if (position == vector.end()) return 0;
    return position - vector.begin();
}

float RoundERROR(float value);

float RoundToDigits(float value, int digits = 3);

float RoundToERROR(float value, float error);

float FloorToDigits(float value, int digits = 2);

float CeilToDigits(float value, int digits = 2);

}
