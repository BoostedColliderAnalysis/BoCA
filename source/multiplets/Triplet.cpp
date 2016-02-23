/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "multiplets/Triplet.hh"

namespace boca
{

Doublet const& Triplet::Doublet() const
{
    return Multiplet1();
}

Doublet& Triplet::Doublet()
{
    return Multiplet1();
}

Singlet const& Triplet::Singlet() const
{
    return Multiplet2();
}

void Triplet::SetSubJettiness()
{
  sub_jettiness_ = boca::SubJettiness(Singlet().Jet());
}

Momentum Triplet::LeptonPt() const
{
  return lepton_pt_;
}

void Triplet::SetLeptonPt(Momentum pt)
{
  lepton_pt_ = pt;
}

}
