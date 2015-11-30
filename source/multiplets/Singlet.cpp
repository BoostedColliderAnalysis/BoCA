/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <boost/units/absolute.hpp>

#include "multiplets/Singlet.hh"
#include "DetectorGeometry.hh"
#include "Vector.hh"
#include "physics/Math.hh"
#include "Debug.hh"

namespace boca
{

Singlet::Singlet(boca::Jet const& jet)
{
    Info0;
    jet_ = jet;
}

Singlet::Singlet(fastjet::PseudoJet const& jet)
{
    Info0;
    jet_ = jet;
}

bool Singlet::Overlap(boca::Jet const& jet) const
{
    return Close(jet)(Jet());
}

bool Singlet::Overlap(Singlet const& singlet) const
{
    return Overlap(singlet.Jet());
}

Angle Singlet::Radius(boca::Jet const& jet) const
{
    Info0;
    if (!jet.has_constituents()) return 0;
    Angle delta_r = 0_rad;
    for (auto const & constituent : jet.constituents()) {
        Angle constituent_delta_r = jet.DeltaRTo(constituent);
        Debug(constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float Singlet::Spread(boca::Jet const& jet) const
{
    Info0;
    if (!jet.has_constituents()) return 0;
//     Angle delta_r = Radius(jet);
    Angle delta_r = 0;
    float spread = 0;
    for (auto const & constituent : jet.constituents()) {
        Angle constituent_delta_r = jet.DeltaRTo(constituent);
        spread += constituent_delta_r / rad * constituent.pt();
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    if (delta_r == 0_rad) return 0;
    return spread / jet.pt() / delta_r * rad;
}

void Singlet::SetBdt(float bdt)
{
    jet_.Info().SetBdt(bdt);
}

JetInfo const& Singlet::UserInfo() const
{
    return jet_.Info();
}

float Singlet::log(Length length) const
{
    INFO(length);
    if (length > 0_mm) return std::log10(length / mm);
    return std::log10(DetectorGeometry::TrackerDistanceMin() / 10_mm);
}

int Singlet::Charge() const
{
//       return UserInfo().Charge();
    return sgn(UserInfo().Charge());
}

using AngleSquareMomentum = ValueProduct<AngleSquare, Momentum>;

Vector2<AngleSquare> Singlet::Pull() const
{
    if (has_pull_) return pull_;
    if (!jet_.has_constituents()) return {};
    std::vector<boca::Jet> constituents = JetVector(jet_.constituents());
    if (constituents.size() < 3) return {};
    Vector2<AngleSquare> sum;
    for (auto const & constituent : constituents) sum += Reference(constituent) * constituent.pt() * constituent.DeltaRTo(jet_);
    pull_ = sum  / jet_.pt();
    has_pull_ = true;
    return pull_;
}

const Singlet& Singlet::singlet() const
{
    return *this;
}

}
