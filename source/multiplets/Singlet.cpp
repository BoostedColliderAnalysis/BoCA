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
    Angle delta_r = 0_rad;
    for (auto const & constituent : jet.Constituents()) {
        Angle constituent_delta_r = jet.DeltaRTo(constituent);
        DEBUG(constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}
using AngleMomentum = ValueProduct<Angle, Momentum>;

double Singlet::Spread(boca::Jet const& jet) const
{
    INFO0;
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

void Singlet::SetBdt(double bdt)
{
    Info().SetBdt(bdt);
}

double Singlet::Bdt() const
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

double Singlet::Log(Length length) const
{
    INFO(length);
    return std::log10(length < nm ? DetectorGeometry::TrackerDistanceMin() / cm : length / mm);
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
    auto constituents = Constituents();
    if (constituents.size() < 3) return {};
    Vector2<AngleSquare> sum;
    for (auto const & constituent : constituents) sum += PseudoJet::DeltaTo(constituent) * constituent.pt() * PseudoJet::DeltaRTo(constituent);
    pull_ = sum  / pt();
    has_pull_ = true;
    return pull_;
}

const Singlet& Singlet::ConstituentJet() const
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
double Singlet::MaxDisplacement() const
{
    return Log(Info().MaxDisplacement());
}
double Singlet::MeanDisplacement() const
{
    return Log(Info().MeanDisplacement());
}
double Singlet::SumDisplacement() const
{
    return Log(Info().SumDisplacement());
}
Angle Singlet::Radius() const
{
    return Radius(Jet());
}
double Singlet::Spread() const
{
    return Spread(Jet());
}
Angle Singlet::VertexRadius() const
{
    return Radius(Info().VertexJet());
}
double Singlet::VertexSpread() const
{
    return Spread(Info().VertexJet());
}
double Singlet::EnergyFraction() const
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
double Singlet::CoreEnergyFraction() const
{
    return Info().CoreEnergyFraction(Jet());
}
double Singlet::FlightPath() const
{
    return Log(Info().MeanDisplacement());
}
double Singlet::TrtHtFraction() const
{
    return Spread(Info().VertexJet());
}
Momentum Singlet::Ht() const
{
    return Pt();
}

}
