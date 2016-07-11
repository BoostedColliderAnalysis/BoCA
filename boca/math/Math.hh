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
template <typename Value_>
int sgn(Value_ value)
{
    return (Value_(0) < value) - (value < Value_(0));
}

template <typename Value_>
int LowerBound(std::vector<Value_> const& vector, Value_ value)
{
    auto position = boost::range::lower_bound(vector, value, [](double value_1, double value_2) {
        return value_1 > value_2;
    });
    if (position == vector.end()) return 0;
    return position - vector.begin();
}

template <typename Value_>
int UpperBound(std::vector<Value_> const& vector, Value_ value)
{
    auto position = boost::range::upper_bound(vector, value, [](double value_1, double value_2) {
        return value_1 > value_2;
    });
    if (position == vector.end()) return 0;
    return position - vector.begin();
}

double RoundError(double value);

double RoundToDigits(double value, int digits = 3);

double RoundToError(double value, double error);

double FloorToDigits(double value, int digits = 2);

double CeilToDigits(double value, int digits = 2);

}
