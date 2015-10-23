/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <algorithm>
#include <boost/range/algorithm/lower_bound.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include "Units.hh"

namespace boca
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
    auto position = boost::range::lower_bound(vector, value, [](float a, float b) {
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

template <typename Value>
Value min(std::vector<Value> vector, bool truncate = false)
{
    if (truncate) vector.erase(std::remove(vector.begin(), vector.end(), 0.), vector.end());
    return *boost::range::min_element(vector);
}

// template <>
Crosssection min(std::vector<Crosssection> vector, bool truncate = false);

template <typename Value>
Value max(std::vector<Value> const& vector)
{
    return *boost::range::max_element(vector);
}

template <typename Value>
std::pair<Value, Value> minmax(std::vector<Value> const& vector)
{
    return *std::minmax_element(vector.begin(), vector.end());
}

}
