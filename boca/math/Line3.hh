/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/math/Line.hh"
#include "boca/math/Vector3.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Line between two points in three dimensional space
 */
template<typename Value_>
using Line3 = Line<Vector3, Value_>;

}
