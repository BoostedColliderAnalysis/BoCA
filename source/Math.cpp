/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Math.hh"

#include <cmath>

#include "Debug.hh"

namespace boca
{

float Distance(float rapidity_1, float phi_1, float rapidity_2, float phi_2)
{
    return std::sqrt(sqr(rapidity_2 - rapidity_1) + sqr(DeltaPhi(phi_2, phi_1)));
}

float Length(float rapidity, float phi)
{
    return std::sqrt(sqr(rapidity) + sqr(phi));
}

float DeltaPhi(float phi_1, float phi_2)
{
    return RestrictPhi(phi_1 - phi_2);
}

float RestrictPhi(float phi)
{
    while (std::abs(phi) > M_PI) {
        if (phi < - M_PI) phi += 2 * M_PI;
        else if (phi > M_PI) phi -= 2 * M_PI;
        else Error(phi);
    }
    return phi;
}

int LargeNumber()
{
    return 999999999;
}

float FloorToDigits(float value, int digits)
{
    if (value == 0 || value != value) {
        return 0;
    } else {
        float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
        return std::floor(value * factor) / factor;
    }
}

float CeilToDigits(float value, int digits)
{
    if (value == 0 || value != value) {
        return 0;
    } else {
        float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
        return std::ceil(value * factor) / factor;
    }
}

float RoundError(float value)
{
    return RoundToDigits(value, 2);
}


float RoundToDigits(float value, int digits)
{
    Debug();
    if (value == 0 || value != value) return 0;
    float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
    return std::round(value * factor) / factor;

}

float RoundToError(float value, float error)
{
    Debug();
    if (value == 0 || value != value) return 0;
    float factor = std::pow(10.0, 2 - std::ceil(std::log10(std::abs(error))));
    return std::round(value * factor) / factor;
}

}

