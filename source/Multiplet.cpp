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

fastjet::PseudoJet Multiplet::Jet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) const
{
    boca::Jets constituents;
    if (jet_1.has_user_info() && jet_1.user_info<JetInfo>().SubStructure() && jet_1.has_constituents()) constituents = jet_1.constituents();
    else constituents.emplace_back(jet_1);
    if (jet_2.has_user_info() && jet_2.user_info<JetInfo>().SubStructure() && jet_2.has_constituents()) constituents = Join(constituents, jet_2.constituents());
    else constituents.emplace_back(jet_2);

    fastjet::PseudoJet jet = fastjet::join(constituents, InfoRecombiner());
    if (int((jet_1 + jet_2).m()) != int(jet.m())) {
        constituents = fastjet::sorted_by_pt(constituents);
        constituents.erase(std::unique(constituents.begin(), constituents.end()), constituents.end());
    }
    jet = fastjet::join(constituents, InfoRecombiner());
    Check(int((jet_1 + jet_2).m()) == int(jet.m()), jet.m(), (jet_1 + jet_2).m(), jet_1.m(), jet_2.m());

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

float Multiplet::DeltaR(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    float delta_r = multiplets_1.Jet().delta_R(multiplets_2.Jet());
    if (std::abs(delta_r) > 100) delta_r = 0;
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

float Multiplet::Rho(MultipletBase const& jet_1, MultipletBase const& jet_2) const
{
    if (Jet(jet_1.Jet(), jet_2.Jet()).pt() < DetectorGeometry::MinCellPt() || DeltaR(jet_1, jet_2) < DetectorGeometry::MinCellResolution()) return 0;
    return Jet().m() / Jet().pt() / DeltaR(jet_1, jet_2) * 2;
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

float Multiplet::Dipolarity(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    if (DeltaR(multiplets_1, multiplets_2) == 0) return 0;
    fastjet::PseudoJet jet = Jet(multiplets_1.Jet(), multiplets_2.Jet());
    if (jet.pt() == 0) return 0;
    float dipolarity = 0;
    if (!jet.has_constituents()) return 0;
    for (auto const & constituent : jet.constituents()) {
        if (constituent.pt() > jet.pt()) continue;

        float phi = constituent.phi_std();
        float distance_1 = Distance(multiplets_1, multiplets_2, Vector2(constituent.rap(), phi));

        if (phi < 0) phi += 2 * M_PI;
        else  phi -= 2 * M_PI;
        float distance_2 =  Distance(multiplets_1, multiplets_2, Vector2(constituent.rap(), phi));

        float distance = std::min(distance_1, distance_2);
        if (distance > DeltaR(multiplets_1, multiplets_2)) continue;
        dipolarity += constituent.pt() * sqr(distance);
    }
    return dipolarity / jet.pt() / sqr(DeltaR(multiplets_1, multiplets_2));
}

float Multiplet::Distance(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2, Vector2 const& point_0) const
{
    Vector2 point_1(multiplets_1.Jet().rap(), multiplets_1.Jet().phi_std());
    Vector2 point_2(multiplets_2.Jet().rap(), multiplets_2.Jet().phi_std());
    return std::abs(point_2.Y() - point_1.Y() * point_0.X() - (point_2.X() - point_1.X()) * point_0.Y() + point_2.X() * point_1.Y() - point_2.Y() * point_1.X()) / DeltaR(multiplets_1, multiplets_2);
}
int Multiplet::Charge(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return sgn(multiplets_1.Charge() + multiplets_2.Charge());
}

float Multiplet::BottomBdt(MultipletBase const& multiplets_1, MultipletBase const& multiplets_2) const
{
    return (multiplets_1.BottomBdt() + multiplets_2.BottomBdt()) / 2 ;
}


}
