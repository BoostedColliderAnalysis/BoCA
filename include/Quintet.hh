/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Triplet.hh"

namespace boca {

class Quintet : public TwoBody<boca::Triplet, boca::Doublet> {

public:

    using TwoBody<boca::Triplet, boca::Doublet>::TwoBody;

    boca::Doublet const& Doublet() const;

    boca::Triplet const& Triplet() const;

};

}
