/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/max_element.hpp>
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

Angle Singlet::Radius() const
{
    INFO0;
    if (has_radius_) return radius_;
    auto constituents = Constituents();
    radius_ = constituents.size() > 1 ? DeltaRTo(*boost::range::max_element(Constituents(), [this](boca::Jet const & jet_1, boca::Jet const & jet_2) {
        return DeltaRTo(jet_1) < DeltaRTo(jet_2);
    })) : 0_rad;
    has_radius_ = true;
    return radius_;
}

using AngleMomentum = ValueProduct<Angle, Momentum>;

double Singlet::Spread() const
{
    INFO0;
    return Radius() > 0_rad && Pt() > 0_eV ? double(boost::accumulate(Constituents(), 0_rad * eV, [this](AngleMomentum & sum, boca::Jet const & constituent) {
        return sum + DeltaRTo(constituent) * constituent.Pt();
    }) / Pt() / Radius()) : 0;
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
    return Info().Charge();
}

using AngleSquareMomentum = ValueProduct<AngleSquare, Momentum>;

Vector2<AngleSquare> Singlet::PullVector() const
{
    if (has_pull_) return pull_;
    auto constituents = Constituents();
    if (constituents.size() < 3) return {};
    auto sum = boost::accumulate(constituents, Vector2<AngleSquareMomentum>(), [this](Vector2<AngleSquareMomentum>& sum , boca::Jet const & constituent) {
        return sum + PseudoJet::DeltaTo(constituent) * constituent.Pt() * PseudoJet::DeltaRTo(constituent);
    });
    pull_ = Pt() > 0_eV ? Vector2<AngleSquare>((sum  / Pt())) : Vector2<AngleSquare>();
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
Angle Singlet::VertexRadius() const
{
    return Info().VertexJet().Radius();
}
double Singlet::VertexSpread() const
{
    return Info().VertexJet().Spread();
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
    return Info().VertexJet().Spread();
}
Momentum Singlet::Ht() const
{
    return Pt();
}

}
