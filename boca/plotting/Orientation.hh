/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

#include "boca/generic/Flag.hh"

namespace boca
{

/**
 * @brief Orientation of the Legend
 *
 * the default position is inside center center
 * only deviations from this position need to be requested
 *
 */
enum class Orientation
{
    none = 0,
    center = 1 << 0,
    left = 1 << 1,
    right = 1 << 2,
    top = 1 << 3,
    bottom = 1 << 4,
    outside = 1 << 5
//     inside = 1 << 6,
};

template<>
struct Flag<Orientation> {
    static const bool enable = true;
};

std::string Name(Orientation orientation);

}
