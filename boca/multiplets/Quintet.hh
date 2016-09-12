/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Triplet.hh"

namespace boca {

/**
* @brief A %Quintet consisting of a Triplet and a Doublet
*
*/
class Quintet : public TwoBody<boca::Triplet, boca::Doublet> {

public:

    using TwoBody<boca::Triplet, boca::Doublet>::TwoBody;

    boca::Doublet const& Doublet() const;

    boca::Triplet const& Triplet() const;

    boca::Doublet & Doublet();

    boca::Triplet & Triplet();

};

}
