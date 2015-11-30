/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "multiplets/Doublet.hh"
#include "SubJettiness.hh"

namespace boca {

class Triplet : public TwoBody<boca::Doublet, boca::Singlet> {

public:

    using TwoBody<boca::Doublet, boca::Singlet>::TwoBody;

    boca::Doublet const& Doublet() const;

    boca::Doublet& Doublet();

    boca::Singlet const& Singlet() const;

    void set_sub_jettiness();

    float pt() const;

    void set_pt(Momentum pt);

    SubJettiness sub_jettiness() const;

private:

    SubJettiness sub_jettiness_;

    Momentum pt_;

};

}
