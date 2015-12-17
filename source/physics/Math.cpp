/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <cmath>

#include "physics/Math.hh"
#include "Debug.hh"

namespace boca
{

namespace
{

float Factor(float value, int digits) {
    return std::pow(10., digits - std::ceil(std::log10(std::abs(value))));
}

}

float FloorToDigits(float value, int digits) {
    if (value == 0 || value != value) return 0;
    float factor = Factor(value, digits);
    return std::floor(value * factor) / factor;
}

float CeilToDigits(float value, int digits) {
    if (value == 0 || value != value) return 0;
    float factor = Factor(value, digits);
    return std::ceil(value * factor) / factor;
}

float RoundError(float value){
    return RoundToDigits(value, 2);
}

float RoundToDigits(float value, int digits) {
    Info0;
    if (value == 0 || value != value) return 0;
    float factor = Factor(value, digits);
    return std::round(value * factor) / factor;
}

float RoundToError(float value, float error) {
    Info0;
    if (value == 0 || value != value) return 0;
    float factor = Factor(error, 2);
    return std::round(value * factor) / factor;
}

}
