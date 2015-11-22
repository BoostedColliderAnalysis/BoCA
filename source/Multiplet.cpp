/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Multiplet.hh"

#include "Line2.hh"
#include "InfoRecombiner.hh"
#include "JetInfo.hh"
#include "Vector.hh"
#include "Math.hh"
#include "Sort.hh"
#include "Units.hh"
#include "Debug.hh"

namespace boca
{

Vector2<float> Multiplet::Pull() const
{
    Error("do not end up here");
    return {};
}

boca::Singlet Multiplet::Singlet(boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const
{
    std::vector<fastjet::PseudoJet> constituents;
    if (singlet_1.Jet().has_constituents()) constituents = singlet_1.Jet().constituents();
    else constituents.emplace_back(singlet_1.Jet());
    if (singlet_2.Jet().has_constituents()) constituents = Join(constituents, singlet_2.Jet().constituents());
    else constituents.emplace_back(singlet_2.Jet());
    constituents = fastjet::sorted_by_pt(constituents);
    constituents.erase(std::unique(constituents.begin(), constituents.end()), constituents.end());
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

float Multiplet::Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Ht() + multiplets_2.Ht();
}

Angle Multiplet::DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Angle delta_rap = multiplets_1.Rap() - multiplets_2.Rap();
    if (boost::units::abs(delta_rap) > 100. * rad) return 0. * rad;
    return delta_rap;
}

Angle Multiplet::DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Jet().delta_phi_to(multiplets_2.Jet()) * rad;
}

Angle Multiplet::DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Angle delta_r = multiplets_1.Jet().DeltaRTo(multiplets_2.Jet());
    if (boost::units::abs(delta_r) > 100. * rad) delta_r = 0. * rad;
//         if (delta_r < DetectorGeometry::MinCellResolution()) delta_r = Singlet(Jet()).DeltaR();
    return delta_r;
}

Mass Multiplet::DeltaM(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Mass() - multiplets_2.Mass();
}

float Multiplet::DeltaHt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Ht() - multiplets_2.Ht();
}

float Multiplet::Rho(MultipletBase const& jet_1, MultipletBase const& jet_2, boca::Jet const& jet) const
{
    Angle delta_r = DeltaR(jet_1, jet_2);
    if (jet.Pt() < DetectorGeometry::MinCellPt() || delta_r < DetectorGeometry::MinCellResolution()) return 0;
    return jet.Mass() / jet.Pt() / delta_r * 2. * rad;
}

Angle Multiplet::Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Vector2<float> pull = multiplets_1.singlet().Pull();
    Vector2<double> ref = multiplets_1.Reference(multiplets_2.Jet());
    float pul_mag = pull.Mod();
    float ref_mag = ref.Mod();
    if (pul_mag == 0 || ref_mag == 0) return M_PI * rad;
    double cos = ref * pull / pul_mag / ref_mag;
    if (cos > 1) cos = 1;
    if (cos < -1) cos = -1;
    return std::acos(cos) * rad;
}

Angle Multiplet::PullDifference(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return Pull(multiplets_1, multiplets_2);
}

Angle Multiplet::PullSum(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return Pull(multiplets_2, multiplets_1);
}

float Multiplet::Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, boca::Singlet const& singlet) const
{
    if (singlet.Pt() == at_rest) return 0;
    if (!singlet.Jet().has_constituents()) return 0;
    Vector2<float> point_1(multiplets_1.Jet().rap(), multiplets_1.Jet().phi_std());
    Vector2<float> point_2 = Point2(point_1, multiplets_2);
    Line2<float> line(point_1, point_2);
    float dipolarity = 0;
    for (auto const & constituent : singlet.Jet().constituents()) dipolarity += constituent.pt() * sqr(Distance(line, constituent));
    double delta_r = DeltaR(multiplets_1, multiplets_2) / rad;
    if (delta_r == 0) return dipolarity / singlet.Jet().pt();
    return dipolarity / singlet.Jet().pt() / sqr(delta_r);
}

Vector2<float> Multiplet::Point2(Vector2<float> const& point_1, MultipletBase const& multiplets_2)const
{
    double phi = multiplets_2.Jet().phi_std();
    Vector2<float> point_2(multiplets_2.Jet().rap(), phi);
    float distance_1 = (point_1 - point_2).Mod2();
    phi -= sgn(phi) * 2. * M_PI;
    Vector2<float> point_3(multiplets_2.Jet().rap(), phi);
    float distance_2 = (point_1 - point_3).Mod2();
    if (distance_2 < distance_1) return point_3;
    return point_2;
}

float Multiplet::Distance(Line2<float> const& line, boca::Jet const& constituent) const
{
    float phi = constituent.phi_std();
    float distance_1 = line.DistanceToSegment(Vector2<float>(constituent.rap(), phi));
    phi -= sgn(phi) * 2. * M_PI;
    float distance_2 = line.DistanceToSegment(Vector2<float>(constituent.rap(), phi));
    return std::min(distance_1, distance_2);
}

int Multiplet::Charge(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return sgn(multiplets_1.Charge() + multiplets_2.Charge());
}

float Multiplet::BottomBdt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return (multiplets_1.BottomBdt() + multiplets_2.BottomBdt()) / 2 ;
}

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

}


