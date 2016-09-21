#pragma once

#include "boca/math/GradedContainer.hh"
#include "boca/math/Matrix3.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Graded three dimensional matrix
 */
template<typename Value_>
using GradedMatrix3 = GradedMatrix<Matrix3, Value_>;

}
