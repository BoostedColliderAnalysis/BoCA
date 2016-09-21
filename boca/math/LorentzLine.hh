/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/math/Line.hh"
#include "boca/math/LorentzVector.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Line between two points in Lorentz space
 */
template<typename Value_>
using LorentzLine = Line<LorentzVector,  Value_>;

}
