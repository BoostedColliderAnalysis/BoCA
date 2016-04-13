/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <cmath>

#include "math/Math.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace
{

double Factor(double value, int digits) {
    return std::pow(10., digits - std::ceil(std::log10(std::abs(value))));
}

}

double FloorToDigits(double value, int digits) {
    if (value == 0 || value != value) return 0;
    auto factor = Factor(value, digits);
    return std::floor(value * factor) / factor;
}

double CeilToDigits(double value, int digits) {
    if (value == 0 || value != value) return 0;
    auto factor = Factor(value, digits);
    return std::ceil(value * factor) / factor;
}

double RoundError(double value){
    return RoundToDigits(value, 2);
}

double RoundToDigits(double value, int digits) {
    INFO0;
    if (value == 0 || value != value) return 0;
    auto factor = Factor(value, digits);
    return std::round(value * factor) / factor;
}

double RoundToError(double value, double error) {
    INFO0;
    if (value == 0 || value != value) return 0;
    auto factor = Factor(error, 2);
    return std::round(value * factor) / factor;
}

}
