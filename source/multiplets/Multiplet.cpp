/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/math/constants/constants.hpp>
#include <boost/range/algorithm/unique.hpp>

#include "physics/Math.hh"
#include "Vector.hh"
#include "Sort.hh"
#include "Line2.hh"
#include "multiplets/Multiplet.hh"
#include "DEBUG.hh"

namespace boca
{

boca::Singlet Multiplet::Singlet(boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const
{
    std::vector<fastjet::PseudoJet> constituents(singlet_1.has_constituents() ? singlet_1.constituents() : PseudoJetVector(singlet_1.Jets()));
    constituents = Join(constituents, singlet_2.has_constituents() ? singlet_2.constituents() : PseudoJetVector(singlet_2.Jets()));
    constituents = fastjet::sorted_by_pt(constituents);
    boost::erase(constituents, boost::unique<boost::return_next_end>(constituents));
    return fastjet::join(constituents, InfoRecombiner());
}

boca::Jet Multiplet::Jet(boca::Jet const& jet_1, boca::Jet const& jet_2) const
{
    boca::Jet jet = fastjet::join(jet_1, jet_2, InfoRecombiner());
    return jet;
}

Momentum Multiplet::DeltaPt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Momentum delta_pt  = multiplets_1.Pt() - multiplets_2.Pt();
    if (delta_pt != delta_pt) return at_rest;
    return delta_pt;
}

Momentum Multiplet::Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Ht() + multiplets_2.Ht();
}

Angle Multiplet::DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Angle delta_rap = multiplets_1.Rap() - multiplets_2.Rap();
    if (boost::units::abs(delta_rap) > 100_rad) return 0_rad;
    return delta_rap;
}

Angle Multiplet::DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Jet().delta_phi_to(multiplets_2.Jet()) * rad;
}

Angle Multiplet::DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Angle delta_r = multiplets_1.DeltaRTo(multiplets_2.Jet());
    if (boost::units::abs(delta_r) > 100_rad) delta_r = 0_rad;
//         if (delta_r < DetectorGeometry::MinCellResolution()) delta_r = Singlet(Jet()).DeltaR();
    return delta_r;
}

Mass Multiplet::DeltaM(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Mass() - multiplets_2.Mass();
}

Momentum Multiplet::DeltaHt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Ht() - multiplets_2.Ht();
}

float Multiplet::Rho(MultipletBase const& jet_1, MultipletBase const& jet_2, boca::Jet const& jet) const
{
    Angle delta_r = DeltaR(jet_1, jet_2);
    if (jet.Pt() < DetectorGeometry::MinCellPt() || delta_r < DetectorGeometry::MinCellResolution()) return 0;
    return jet.Mass() / jet.Pt() / delta_r * 2_rad;
}

Angle Multiplet::Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Vector2<AngleSquare> pull = multiplets_1.singlet().PullVector();
    Vector2<Angle> ref = multiplets_1.Reference(multiplets_2.Jet());
    AngleSquare pul_mag = pull.Mod();
    Angle ref_mag = ref.Mod();
    if (pul_mag == 0. * rad2 || ref_mag == 0_rad) return boost::math::constants::pi<double>() * rad;
    double cos = ref * pull / ref_mag / pul_mag;
    if (cos > 1) cos = 1;
    if (cos < -1) cos = -1;
    return std::acos(cos) * rad;
//     return boost::units::acos(cos * boost::units::si::si_dimensionless);
}

float Multiplet::Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, boca::Singlet const& singlet) const
{
    if (singlet.Pt() == at_rest) return 0;
    if (!singlet.has_constituents()) return 0;
    Vector2<Angle> point_1(multiplets_1.Rap(), multiplets_1.Phi());
    Vector2<Angle> point_2 = Point2(point_1, multiplets_2);
    Line2<Angle> line(point_1, point_2);
    auto dipolarity = at_rest * rad2;
    for (auto const & constituent : singlet.Constituents()) dipolarity += constituent.Pt() * sqr(Distance(line, constituent));
    Angle delta_r = DeltaR(multiplets_1, multiplets_2);
    if (delta_r == 0_rad) return dipolarity / singlet.Pt() / rad2;
    float dip = dipolarity / singlet.Pt() / sqr(delta_r);
    CHECK(dip < 10, dip, dipolarity, singlet.Pt(), delta_r);
    return dip;
}

Vector2<Angle> Multiplet::Point2(Vector2<Angle> const& point_1, MultipletBase const& multiplets_2)const
{
    Angle phi = multiplets_2.Phi();
    Vector2<Angle> point_2(multiplets_2.Rap(), phi);
    auto distance_1 = (point_1 - point_2).Mod2();
    phi = Wrap(phi);
    Vector2<Angle> point_3(multiplets_2.Rap(), phi);
    auto distance_2 = (point_1 - point_3).Mod2();
    if (distance_2 < distance_1) return point_3;
    return point_2;
}

Angle Multiplet::Distance(Line2<Angle> const& line, boca::Jet const& constituent) const
{
    Angle phi = constituent.Phi();
    Angle distance_1 = line.DistanceToSegment(Vector2<Angle>(constituent.Rap(), phi));
    phi = Wrap(phi);
    Angle distance_2 = line.DistanceToSegment(Vector2<Angle>(constituent.Rap(), phi));
    return std::min(distance_1, distance_2);
}

int Multiplet::Charge(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return sgn(multiplets_1.Charge() + multiplets_2.Charge());
}

// float Multiplet::BottomBdt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
// {
//     return (multiplets_1.BottomBdt() + multiplets_2.BottomBdt()) / 2 ;
// }

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

}


