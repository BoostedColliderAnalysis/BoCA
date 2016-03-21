/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/math/constants/constants.hpp>

#include "multiplets/Singlet.hh"
#include "DetectorGeometry.hh"
#include "Vector.hh"
#include "physics/Math.hh"
#include "physics/Range.hh"
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
    return radius_.Get([this]() {
        return GetRadius();
    });
}

Angle Singlet::GetRadius() const
{
    INFO0;
    auto constituents = Constituents();
    return constituents.size() > 1 ? DeltaRTo(*boost::range::max_element(constituents, [this](boca::Jet const & jet_1, boca::Jet const & jet_2) {
        return DeltaRTo(jet_1) < DeltaRTo(jet_2);
    })) : 0_rad;
}

using AngleMomentum = ValueProduct<Angle, Momentum>;

double Singlet::Spread() const
{
    INFO0;
    return Radius() > 0_rad && Pt() > 0_eV ? double(boost::accumulate(Constituents(), 0_rad * eV, [this](AngleMomentum & sum, boca::Jet const & constituent) {
        return sum + DeltaRTo(constituent) * constituent.Pt();
    }) / Pt() / Radius()) : 0;
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

Vector2<AngleSquare> Singlet::Pull() const
{
    INFO0;
    return pull_.Get([this]() {
        return GetPull();
    });
}


Vector2<AngleSquare> Singlet::GetPull() const
{
    if (Pt() <= 0_eV || !has_constituents()) return {};
//     auto constituents = Constituents();
//     if (constituents.size() < 3) return {};
//     if (!has_constituents()) return {};
    return boost::accumulate(Constituents(), Vector2<AngleSquareMomentum>(), [this](Vector2<AngleSquareMomentum>& sum , boca::Jet const & constituent) {
        return sum + DeltaTo(constituent) * constituent.Pt() * DeltaRTo(constituent);
    }) / Pt();
}

AngleSquareMomentum Singlet::Dipolarity(const Line2< Angle >& line) const
{
    if (!has_constituents()) return 0;
    return boost::accumulate(Constituents(), at_rest * rad2, [&](AngleSquareMomentum & sum, boca::Jet const & constituent) {
        return sum + constituent.Pt() * sqr(line.Distance(constituent));
    });
}

Angle Singlet::Pull(const Vector2< Angle >& reference) const
{
    if (reference.Mod2() <= 0. * rad2 || Pull().Mod2() <= 0. * rad2 * rad2) return boost::math::constants::pi<double>() * rad;
    Range<double> range(-1, 1);
    return std::acos(range.Constrain(reference * Pull() / reference.Mod() / Pull().Mod())) * rad;
    //     return boost::units::acos(cos * boost::units::si::si_dimensionless);
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

void Singlet::Enforce(const boca::Jet& jet, double bdt)
{
    reset(jet);
    ResetInfo(jet.Info());
    SetBdt(bdt);
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

}
