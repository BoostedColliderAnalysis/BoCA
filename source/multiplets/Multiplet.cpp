/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boca/multiplets/Sort.hh"
#include "boca/multiplets/Multiplet.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

void Multiplet::SetClosestLepton(std::vector<boca::Lepton> const& leptons)
{
    closest_lepton_ = ClosestLepton(Jet(), leptons);
}

ClosestLepton Multiplet::Lepton() const
{
    return closest_lepton_;
}

Singlet Multiplet::ConstituentJet() const
{
    return constituent_jet_.Get([this]() {
        return GetConstituentJet();
    });
}

Jet Multiplet::Jet() const
{
    return jet_.Get([this]() {
        return GetJet();
    });
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

Vector2< Angle > Multiplet::Angles(bool wrap_phi) const
{
    return Jet().Angles(wrap_phi);
}

boca::SubJettiness Multiplet::SubJettiness() const
{
    return boca::SubJettiness(ConstituentJet());
}

boca::Mass Multiplet::Mass() const
{
    return Jet().Mass();
}

std::vector<boca::Jet> Multiplet::Constituents() const
{
    return ConstituentJet().Constituents();
}

Angle Multiplet::DeltaPhiTo(PseudoJet const& jet) const
{
    return Jet().DeltaPhiTo(jet);
}

Angle Multiplet::DeltaRTo(PseudoJet const& jet) const
{
    return Jet().DeltaRTo(jet);
}

Angle Multiplet::DeltaRapTo(PseudoJet const& jet) const
{
    return Jet().DeltaRapTo(jet);
}

Vector2< Angle > Multiplet::DeltaTo(PseudoJet const& jet) const
{
    return Jet().DeltaTo(jet);
}

Vector2< Angle > Multiplet::AnglesMinTo(PseudoJet const& jet) const
{
    return Jet().AnglesMinTo(jet);
}

bool Multiplet::HasConstituents() const
{
    return ConstituentJet().HasConsitutents();
}

}


