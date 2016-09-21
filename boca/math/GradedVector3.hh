#pragma once

#include "boca/math/Vector3.hh"
#include "boca/math/GradedContainer.hh"

namespace boca
{

/**
* @ingroup Math
* @brief Graded three dimensional vector
*/
template<typename Value_>
using GradedVector3 = GradedVector<Vector3, Value_>;

}
