/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Multiplet.hh"

#include "Line2.hh"
#include "InfoRecombiner.hh"
#include "JetInfo.hh"
#include "Vector.hh"
#include "Math.hh"
#include "Debug.hh"

namespace boca
{

Vector2 Multiplet::Pull() const
{
    Error("do not end up here");
    return Vector2();
}

boca::Singlet Multiplet::Singlet(boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const
{
    boca::Jets constituents;
    if (singlet_1.Jet().has_user_info() && singlet_1.Jet().user_info<JetInfo>().SubStructure() && singlet_1.Jet().has_constituents()) constituents = singlet_1.Jet().constituents();
    else constituents.emplace_back(singlet_1.Jet());
    if (singlet_2.Jet().has_user_info() && singlet_2.Jet().user_info<JetInfo>().SubStructure() && singlet_2.Jet().has_constituents()) constituents = Join(constituents, singlet_2.Jet().constituents());
    else constituents.emplace_back(singlet_2.Jet());
    constituents = fastjet::sorted_by_pt(constituents);
    constituents.erase(std::unique(constituents.begin(), constituents.end()), constituents.end());
    return fastjet::join(constituents, InfoRecombiner());
}

fastjet::PseudoJet Multiplet::Jet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) const
{
    fastjet::PseudoJet jet = fastjet::join(jet_1, jet_2, InfoRecombiner());
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
    Angle delta_r = to_angle(multiplets_1.Jet().delta_R(multiplets_2.Jet()));
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

float Multiplet::Rho(MultipletBase const& jet_1, MultipletBase const& jet_2, fastjet::PseudoJet const& jet) const
{
    Angle delta_r = DeltaR(jet_1, jet_2);
    if (jet.pt() * GeV < DetectorGeometry::MinCellPt() || delta_r < DetectorGeometry::MinCellResolution()) return 0;
    return jet.m() / jet.pt() / delta_r * 2. * rad;
}

Angle Multiplet::Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Vector2 pull = multiplets_1.singlet().Pull();
    Vector2 ref = multiplets_1.Reference(multiplets_2.Jet());
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
    Vector2 point_1(multiplets_1.Jet().rap(), multiplets_1.Jet().phi_std());
    Vector2 point_2 = Point2(point_1, multiplets_2);
    Line2 line(point_1, point_2);
    float dipolarity = 0;
    for (auto const & constituent : singlet.Jet().constituents()) dipolarity += constituent.pt() * sqr(Distance(line, constituent) / rad);
    Angle delta_r = DeltaR(multiplets_1, multiplets_2);
    if (delta_r == 0. * rad) return dipolarity / singlet.Jet().pt();
    return dipolarity / singlet.Jet().pt() / sqr(delta_r / rad);
}

Vector2 Multiplet::Point2(Vector2 const& point_1, MultipletBase const& multiplets_2)const
{
    double phi = multiplets_2.Jet().phi_std();
    Vector2 point_2(multiplets_2.Jet().rap(), phi);
    float distance_1 = (point_1 - point_2).Mod();
    phi -= sgn(phi) * 2. * M_PI;
    Vector2 point_3(multiplets_2.Jet().rap(), phi);
    float distance_2 = (point_1 - point_3).Mod();
    if (distance_2 < distance_1) return point_3;
    return point_2;
}

Angle Multiplet::Distance(Line2 const& line, fastjet::PseudoJet const& constituent) const
{
    float phi = constituent.phi_std();
    double distance_1 = line.DistanceToSegment(Vector2(constituent.rap(), phi));
    phi -= sgn(phi) * 2. * M_PI;
    double distance_2 = line.DistanceToSegment(Vector2(constituent.rap(), phi));
    return std::min(distance_1, distance_2) * rad;
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

void Multiplet::SetPlainJet(fastjet::PseudoJet const& jet) const
{
    jet_ = jet;
    has_jet_ = true;
}

}


