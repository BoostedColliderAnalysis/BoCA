#pragma once

#include "boca/math/LorentzVector.hh"
#include "boca/math/GradedContainer.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Graded LorentzVector
 */
template<typename Value_>
using GradedLorentzVector = GradedVector<LorentzVector, Value_>;

}

