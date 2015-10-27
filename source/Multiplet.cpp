/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Multiplet.hh"

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
};

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

float Multiplet::DeltaPt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    float delta_pt  = multiplets_1.Jet().pt() - multiplets_2.Jet().pt();
    if (delta_pt != delta_pt) return 0;
    return delta_pt;
}

float Multiplet::Ht(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Ht() + multiplets_2.Ht();
}

float Multiplet::DeltaRap(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    float delta_rap = multiplets_1.Jet().rap() - multiplets_2.Jet().rap();
    if (std::abs(delta_rap) > 100) return 0;
    return delta_rap;
}

float Multiplet::DeltaPhi(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Jet().delta_phi_to(multiplets_2.Jet());
}

Angle Multiplet::DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Angle delta_r = to_angle(multiplets_1.Jet().delta_R(multiplets_2.Jet()));
    if (boost::units::abs(delta_r) > 100. * rad) delta_r = 0. * rad;
//         if (delta_r < DetectorGeometry::MinCellResolution()) delta_r = Singlet(Jet()).DeltaR();
    return delta_r;
}

float Multiplet::DeltaM(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return multiplets_1.Jet().m() - multiplets_2.Jet().m();
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

float Multiplet::Pull(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    Vector2 pull = multiplets_1.singlet().Pull() - multiplets_1.Reference(multiplets_2.Jet());
    return std::atan2(pull.Y(), pull.X());
}

float Multiplet::PullDifference(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return RestrictPhi(boca::DeltaPhi(Pull(multiplets_1, multiplets_2), Pull(multiplets_2, multiplets_1)) - M_PI) / M_PI;
}

float Multiplet::PullSum(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return RestrictPhi(Pull(multiplets_1, multiplets_2) + Pull(multiplets_2, multiplets_1)) / M_PI;
}

float Multiplet::Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, boca::Singlet const& singlet) const
{
    Angle delta_r = DeltaR(multiplets_1, multiplets_2);
    if (delta_r == 0. * rad) return 0;
    if (singlet.Pt() == at_rest) return 0;
    float dipolarity = 0;
    if (!singlet.Jet().has_constituents()) return 0;
    for (auto const & constituent : singlet.Jet().constituents()) {
        if (constituent.pt() > singlet.Jet().pt()) continue;
        Angle distance = Distance(multiplets_1, multiplets_2, constituent, delta_r);
        if (distance > delta_r) continue;
        dipolarity += constituent.pt() * sqr(distance / rad);
    }
    return dipolarity / singlet.Jet().pt() / sqr(delta_r / rad);
}

Angle Multiplet::Distance(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, fastjet::PseudoJet const& constituent, Angle delta_r) const
{
    Vector2 point_1(multiplets_1.Jet().rap(), multiplets_1.Jet().phi_std());
    Vector2 point_2(multiplets_2.Jet().rap(), multiplets_2.Jet().phi_std());
    float phi = constituent.phi_std();
    Angle distance_1 = Distance(point_1, point_2, Vector2(constituent.rap(), phi), delta_r);
    phi -= sgn(phi) * 2. * M_PI;
    Angle distance_2 =  Distance(point_1, point_2, Vector2(constituent.rap(), phi), delta_r);
    return std::min(distance_1, distance_2);
}

/**
 * @brief Distance between the Point point_0 and the Line (point_1, point_2)
 * @details according to \f$D(P_1, P_2, (x_0, y_0)) = \frac{|(y_2-y_1)x_0-(x_2-x_1)y_0+x_2 y_1-y_2 x_1|}{\sqrt{(y_2-y_1)^2+(x_2-x_1)^2}}\f$
 *
 */
Angle Multiplet::Distance(Vector2 const& point_1, Vector2 const& point_2, Vector2 const& point_0, Angle delta_r) const
{
    return double(std::abs(point_2.Y() - point_1.Y() * point_0.X() - (point_2.X() - point_1.X()) * point_0.Y() + point_2.X() * point_1.Y() - point_2.Y() * point_1.X())) / delta_r * rad * rad;
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


