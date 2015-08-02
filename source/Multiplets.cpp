#include "Multiplets.hh"
#include "JetInfo.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis
{

Vector2 Multiplets::Pull() const
{
    Error("do not end up here");
    return Vector2();
};

fastjet::PseudoJet Multiplets::Jet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, Structure structure) const
{
    if (structure == Structure::vertices) structure |= Structure::plain;
    fastjet::PseudoJet jet;
    if (is(structure, Structure::plain)) jet = fastjet::join(jet_1, jet_2);
    if (is(structure, Structure::constituents)) {
        analysis::Jets constituents;
        if (jet_1.has_constituents()) constituents = Join(constituents, jet_1.constituents());
        if (jet_2.has_constituents()) constituents = Join(constituents, jet_2.constituents());
        jet = fastjet::join(constituents);
    }
    if (is(structure, Structure::vertices)) {
        std::vector<Constituent> constituents;
        std::vector<Constituent> displaced_constituents;
        if (jet_1.has_user_info<JetInfo>()) {
            constituents = Join(constituents, jet_1.user_info<JetInfo>().constituents());
            displaced_constituents = Join(displaced_constituents, jet_1.user_info<JetInfo>().displaced_constituents());
        }
        if (jet_2.has_user_info<JetInfo>()) {
            constituents = Join(constituents, jet_2.user_info<JetInfo>().constituents());
            displaced_constituents = Join(displaced_constituents, jet_2.user_info<JetInfo>().displaced_constituents());
        }
        jet.set_user_info(new JetInfo(constituents, displaced_constituents));
    }
    return jet;
}

float Multiplets::DeltaPt(const Multiplets& multiplets_1, const Multiplets& multiplets_2) const
{
    return multiplets_1.Jet().pt() - multiplets_2.Jet().pt();
}

float Multiplets::Ht(const Object& multiplets_1, const Object& multiplets_2) const
{
    return multiplets_1.Ht() + multiplets_2.Ht();
}

float Multiplets::DeltaRap(const Object& multiplets_1, const Object& multiplets_2) const
{
    float delta_rap = multiplets_1.Jet().rap() - multiplets_2.Jet().rap();
    if (std::abs(delta_rap) > 100) return 0;
    return delta_rap;
}

float Multiplets::DeltaPhi(const Object& multiplets_1, const Object& multiplets_2) const
{
    return multiplets_1.Jet().delta_phi_to(multiplets_2.Jet());
}

float Multiplets::DeltaR(const Object& multiplets_1, const Object& multiplets_2) const
{
    float delta_r = multiplets_1.Jet().delta_R(multiplets_2.Jet());
    if (std::abs(delta_r) > 100) delta_r = 0;
//         if (delta_r < DetectorGeometry::MinCellResolution()) delta_r = Singlet(Jet()).DeltaR();
    return delta_r;
}

float Multiplets::DeltaM(const Object& multiplets_1, const Object& multiplets_2) const
{
    return multiplets_1.Jet().m() - multiplets_2.Jet().m();
}

float Multiplets::DeltaHt(const Object& multiplets_1, const Object& multiplets_2) const
{
    return multiplets_1.Ht() - multiplets_2.Ht();
}

float Multiplets::Rho(const Object& jet_1, const Object& jet_2) const
{
    if (Jet(jet_1.Jet(), jet_2.Jet(), Structure::plain).pt() < DetectorGeometry::MinCellPt() || DeltaR(jet_1, jet_2) < DetectorGeometry::MinCellResolution()) return 0;
    return Jet().m() / Jet().pt() / DeltaR(jet_1, jet_2) * 2;
}

float Multiplets::Pull(const Object& multiplets_1, const Object& multiplets_2) const
{
    Vector2 pull = multiplets_1.singlet().Pull() - multiplets_1.Reference(multiplets_2.Jet());
    return std::atan2(pull.Y(), pull.X());
}

float Multiplets::PullDifference(const Object& multiplets_1, const Object& multiplets_2) const
{
    return RestrictPhi(analysis::DeltaPhi(Pull(multiplets_1, multiplets_2), Pull(multiplets_2, multiplets_1)) - M_PI) / M_PI;
}

float Multiplets::PullSum(const Object& multiplets_1, const Object& multiplets_2) const
{
    return RestrictPhi(Pull(multiplets_1, multiplets_2) + Pull(multiplets_2, multiplets_1)) / M_PI;
}

float Multiplets::Dipolarity(const Object& multiplets_1, const Object& multiplets_2) const
{
    if (DeltaR(multiplets_1, multiplets_2) == 0) return 0;
    fastjet::PseudoJet jet = Jet(multiplets_1.Jet(Structure::constituents), multiplets_2.Jet(Structure::constituents), Structure::constituents);
    if (jet.pt() == 0) return 0;
    float dipolarity = 0;
    if (!jet.has_constituents()) return 0;
    for (const auto & constituent : jet.constituents()) {
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

Vector2 Multiplets::Reference(const fastjet::PseudoJet& vector) const
{
    return Vector2(vector.rap() - Jet().rap(), Jet().delta_phi_to(vector));
}

float Multiplets::Distance(const Object& multiplets_1, const Object& multiplets_2, const Vector2& point_0) const
{
    Vector2 point_1(multiplets_1.Jet().rap(), multiplets_1.Jet().phi_std());
    Vector2 point_2(multiplets_2.Jet().rap(), multiplets_2.Jet().phi_std());
    return std::abs(point_2.Y() - point_1.Y() * point_0.X() - (point_2.X() - point_1.X()) * point_0.Y() + point_2.X() * point_1.Y() - point_2.Y() * point_1.X()) / DeltaR(multiplets_1, multiplets_2);
}

}
