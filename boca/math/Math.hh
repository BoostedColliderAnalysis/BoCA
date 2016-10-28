/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <vector>

#include <boost/range/algorithm/lower_bound.hpp>
#include <boost/range/algorithm/upper_bound.hpp>

namespace boca
{

/**
 * @ingroup Math
 * @{
 */

/**
 * @brief sign of value
 *
 */
template <typename Value_>
int sgn(Value_ value)
{
    return (Value_(0) < value) - (value < Value_(0));
}

/**
 * @brief sign of value
 *
 */
template <typename Value_>
int LowerBound(std::vector<Value_> const& vector, Value_ value)
{
    auto position = boost::range::lower_bound(vector, value, [](double value_1, double value_2) {
        return value_1 > value_2;
    });
    if (position == vector.end()) return 0;
    return position - vector.begin();
}

/**
 * @brief Upper bound of vector
 *
 */
template <typename Value_>
int UpperBound(std::vector<Value_> const& vector, Value_ value)
{
    auto position = boost::range::upper_bound(vector, value, [](double value_1, double value_2) {
        return value_1 > value_2;
    });
    if (position == vector.end()) return 0;
    return position - vector.begin();
}

/**
 * @brief round error two two digits
 *
 */
double RoundError(double value);

/**
 * @brief Round value to digits
 *
 */
double RoundToDigits(double value, int digits = 3);

/**
 * @brief Round value to precision of error
 *
 */
double RoundToError(double value, double error);

/**
 * @brief Floor value to digits
 *
 */
double FloorToDigits(double value, int digits = 2);

/**
 * @brief Ceiling to digits
 *
 */
double CeilToDigits(double value, int digits = 2);

// @}

}
