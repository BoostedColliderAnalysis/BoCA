/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/math/constants/constants.hpp>

#include "boca/multiplets/Singlet.hh"
#include "boca/Settings.hh"
#include "boca/generic/Vector.hh"
#include "boca/math/Math.hh"
#include "boca/physics/Range.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace
{

auto Log(Length const &length)
{
    INFO(length);
    return std::log10(length < nm ? Settings::TrackerDistanceMin() / cm : length / mm);
}

}

bool Singlet::Overlap(boca::Jet const &jet) const
{
    return PseudoJet::DeltaRTo(jet) < Settings::OverlapConeSize();
}

Angle Singlet::Radius() const
{
    INFO0;
    return radius_.Get([this]() {
        auto constituents = Constituents();
        return constituents.size() > 1 ? DeltaRTo(*boost::range::max_element(constituents, [this](boca::Jet const & jet_1, boca::Jet const & jet_2) {
            return DeltaRTo(jet_1) < DeltaRTo(jet_2);
        })) : 0_rad;
    });
}

using AngleMomentum = ValueProduct<Angle, Momentum>;

double Singlet::Spread() const
{
    INFO0;
    return Radius() > 0_rad && Pt() > 0_eV ? static_cast<double>(boost::accumulate(Constituents(), 0_rad * eV, [this](AngleMomentum & sum, boca::Jet const & constituent) {
        return sum + DeltaRTo(constituent) * constituent.Pt();
    }) / Pt() / Radius()) : 0;
}

int Singlet::Charge() const
{
    return Info().Charge();
}

Vector2<AngleSquare> Singlet::Pull() const
{
    INFO0;
    return pull_.Get([this]() -> Vector2<AngleSquare> {
        if (Pt() <= 0_eV || !has_constituents()) return {};
        return boost::accumulate(Constituents(), Vector2<AngleSquareMomentum>(), [this](Vector2<AngleSquareMomentum> &sum , boca::Jet const & constituent) {
            return sum + DeltaTo(constituent) * constituent.Pt() * DeltaRTo(constituent);
        }) / Pt();
    });
}

AngleSquareMomentum Singlet::DipolaritySum(const Line2< Angle > &line) const
{
    if (!has_constituents()) return 0;
    return boost::accumulate(Constituents(), at_rest * rad2, [&](AngleSquareMomentum & sum, boca::Jet const & constituent) {
        return sum + constituent.Pt() * sqr(line.MinDistanceTo(constituent));
    });
}

Angle Singlet::Pull(const Vector2< Angle > &reference) const
{
    if (reference.Mod2() <= 0. * rad2 || Pull().Mod2() <= 0. * rad2 * rad2) return Pi();
    auto range = Range<double>{-1, 1};
    return acos(range.Constrain(reference * Pull() / reference.Mod() / Pull().Mod()));
}

const Singlet &Singlet::ConstituentJet() const
{
    return *this;
}

void Singlet::Enforce(boca::Jet const &jet)
{
    reset(jet);
    ResetInfo(jet.Info());
}

void Singlet::Enforce(boca::Jet const &jet, double bdt)
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
    return Energy() > 0_eV ? static_cast<double>(Info().VertexEnergy() / Energy()) : 0.;
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


double Singlet::EnergyRatio() const
{
    return Info().EnergyRatio();
}


double Singlet::MomentumRatio() const
{
    return Info().MomentumRatio();
}


std::vector<boca::LorentzVector<Momentum>> Singlet::LorentzVectors() const
{
    return {Vector()};
}

}
