/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/units/absolute.hpp>

#include "multiplets/Singlet.hh"
#include "DetectorGeometry.hh"
#include "Vector.hh"
#include "physics/Math.hh"
#include "DEBUG.hh"

namespace boca
{

bool Singlet::Overlap(boca::Jet const& jet) const
{
    return Close(jet, DetectorGeometry::OverlapConeSize())(Jet());
}

bool Singlet::Overlap(Singlet const& singlet) const
{
    return Overlap(singlet.Jet());
}

Angle Singlet::Radius(boca::Jet const& jet) const
{
    INFO0;
    if (!jet.has_constituents()) return 0;
    Angle delta_r = 0_rad;
    for (auto const & constituent : jet.Constituents()) {
        Angle constituent_delta_r = jet.DeltaRTo(constituent);
        DEBUG(constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}
using AngleMomentum = ValueProduct<Angle, Momentum>;

float Singlet::Spread(boca::Jet const& jet) const
{
    INFO0;
    if (!jet.has_constituents()) return 0;
//     Angle delta_r = Radius(jet);
    Angle delta_r = 0;
    AngleMomentum spread = 0_rad * GeV;
    for (auto const & constituent : jet.Constituents()) {
        Angle constituent_delta_r = jet.DeltaRTo(constituent);
        spread += constituent_delta_r * constituent.Pt();
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    if (delta_r == 0_rad) return 0;
    return spread / jet.Pt() / delta_r;
}

void Singlet::SetBdt(float bdt)
{
    Info().SetBdt(bdt);
}

float Singlet::Bdt() const
{
    return Info().Bdt();
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
    return sgn(Info().Charge());
}

using AngleSquareMomentum = ValueProduct<AngleSquare, Momentum>;

Vector2<AngleSquare> Singlet::PullVector() const
{
    if (has_pull_) return pull_;
    if (!has_constituents()) return {};
    std::vector<boca::Jet> constituents = Constituents();
    if (constituents.size() < 3) return {};
    Vector2<AngleSquare> sum;
    for (auto const & constituent : constituents) sum += Reference(constituent) * constituent.pt() * constituent.DeltaRTo(*this);
    pull_ = sum  / pt();
    has_pull_ = true;
    return pull_;
}

const Singlet& Singlet::singlet() const
{
    return *this;
}

}
