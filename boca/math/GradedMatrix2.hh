#pragma once

#include "boca/math/GradedContainer.hh"
#include "boca/math/Matrix2.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Graded three two matrix
 */
template<typename Value_>
using GradedMatrix2 = GradedMatrix<Matrix2, Value_>;

}
