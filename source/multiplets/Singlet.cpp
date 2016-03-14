/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "multiplets/Singlet.hh"
#include "DetectorGeometry.hh"
#include "Vector.hh"
#include "physics/Math.hh"
#include "DEBUG.hh"

namespace boca
{

bool Singlet::Overlap(boca::Jet const& jet) const
{
    return PseudoJet::DeltaRTo(jet) < DetectorGeometry::OverlapConeSize();
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

void Singlet::SetTag(boca::Tag tag)
{
  Info().SetTag(tag);
}

boca::Tag Singlet::Tag() const
{
  return Info().Tag();
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
    for (auto const & constituent : constituents) sum += PseudoJet::DeltaTo(constituent) * constituent.pt() * PseudoJet::DeltaRTo(constituent);
    pull_ = sum  / pt();
    has_pull_ = true;
    return pull_;
}

const Singlet& Singlet::singlet() const
{
    return *this;
}

void Singlet::Enforce(const boca::Jet& jet)
{
    reset(jet);
    ResetInfo(jet.Info());
}
Jet Singlet::Jet() const
{
    return *this;
}
std::vector< Jet > Singlet::Jets() const
{
    return {*this};
}
float Singlet::MaxDisplacement() const
{
    return log(Info().MaxDisplacement());
}
float Singlet::MeanDisplacement() const
{
    return log(Info().MeanDisplacement());
}
float Singlet::SumDisplacement() const
{
    return log(Info().SumDisplacement());
}
Angle Singlet::Radius() const
{
    return Radius(Jet());
}
float Singlet::Spread() const
{
    return Spread(Jet());
}
Angle Singlet::VertexRadius() const
{
    return Radius(Info().VertexJet());
}
float Singlet::VertexSpread() const
{
    return Spread(Info().VertexJet());
}
float Singlet::EnergyFraction() const
{
    return Info().VertexEnergy() / Energy();
}
Angle Singlet::EmRadius() const
{
    return Info().ElectroMagneticRadius(Jet());
}
Angle Singlet::TrackRadius() const
{
    return Info().TrackRadius(Jet());
}
float Singlet::CoreEnergyFraction() const
{
    return Info().CoreEnergyFraction(Jet());
}
float Singlet::FlightPath() const
{
    return log(Info().MeanDisplacement());
}
float Singlet::TrtHtFraction() const
{
    return Spread(Info().VertexJet());
}
Momentum Singlet::Ht() const
{
    return Pt();
}

}
