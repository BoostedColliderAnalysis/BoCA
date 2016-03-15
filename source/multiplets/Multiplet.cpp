/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "Sort.hh"
#include "multiplets/Multiplet.hh"
#include "DEBUG.hh"

namespace boca
{

void Multiplet::SetSinglet(boca::Singlet const& singlet) const
{
    singlet_ = singlet;
    has_singlet_ = true;
}

void Multiplet::SetPlainJet(boca::Jet const& jet) const
{
    jet_ = jet;
    has_jet_ = true;
}

void Multiplet::SetLeptonPt(const Momentum& lepton_pt)
{
    lepton_pt_ = lepton_pt;
}

void Multiplet::SetLeptonDeltaR(const Angle& lepton_delta_r)
{
    lepton_delta_r_ = lepton_delta_r;
}

Momentum Multiplet::LeptonPt() const
{
    return lepton_pt_;
}

Angle Multiplet::LeptonDeltaR() const
{
    return lepton_delta_r_;
}

const Singlet& Multiplet::singlet() const
{
    if (!has_singlet_) SetSinglet();
    return singlet_;
}

Jet Multiplet::Jet() const
{
    if (!has_jet_) SetPlainJet();
    return jet_;
}

Momentum Multiplet::Pt() const
{
    return Jet().Pt();
}

Angle Multiplet::Rap() const
{
    return Jet().Rap();
}

Angle Multiplet::Phi() const
{
    return Jet().Phi();
}

void Multiplet::SetSubJettiness()
{
    sub_jettiness_ = boca::SubJettiness(Singlet());
}

boca::SubJettiness Multiplet::SubJettiness() const
{
    return sub_jettiness_;
}

boca::Mass Multiplet::Mass() const
{
    return Jet().Mass();
}
std::vector<boca::Jet> Multiplet::Constituents() const
{
    return Jet().Constituents();
}

}


