#pragma once

#include "boca/math/GradedContainer.hh"
#include "boca/math/Vector2.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Two vector with associated number
 */
template<typename Value_>
using GradedVector2 = GradedVector<Vector2, Value_>;

}

