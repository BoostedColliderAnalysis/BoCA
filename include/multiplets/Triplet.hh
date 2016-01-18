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

    void SetSubJettiness();

    Momentum LeptonPt() const;

    void SetLeptonPt(Momentum pt);

    boca::SubJettiness SubJettiness() const;

private:

    boca::SubJettiness sub_jettiness_;

    Momentum lepton_pt_;

};

}
