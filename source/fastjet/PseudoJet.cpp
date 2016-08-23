/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "TLorentzVector.h"
#include "boca/math/LorentzVector.hh"
#include "boca/fastjet/PseudoJet.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

PseudoJet::PseudoJet() :
    fastjet::PseudoJet()
{
//     ALIVE()
}

PseudoJet::PseudoJet(TLorentzVector const& vector) :
    fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E())
{
    INFO(vector.Px(), px(), vector.Py(), py());
}

PseudoJet::PseudoJet(LorentzVector<Momentum> const& vector) :
    fastjet::PseudoJet(vector.Px() / GeV, vector.Py() / GeV, vector.Pz() / GeV, vector.E() / GeV)
{
    INFO0;
}

Momentum PseudoJet::Pt() const
{
    return pt() * GeV;
}

Mass PseudoJet::Mass() const
{
    return m() > 0 ? m() * GeV : massless;
}

Angle PseudoJet::DeltaRTo(const PseudoJet& jet) const
{
    auto delta_r = delta_R(jet);
    if (delta_r == fastjet::pseudojet_invalid_rap || delta_r > 100) return 0_rad;
    return delta_r * rad;
}

Angle PseudoJet::DeltaRTo(LorentzVector< Momentum > const& lorentz_vector) const
{
    auto jet = fastjet::PseudoJet{lorentz_vector.X() / GeV, lorentz_vector.Y() / GeV, lorentz_vector.Z() / GeV, lorentz_vector.T() / GeV};
    return DeltaRTo(jet);
}

Angle PseudoJet::DeltaPhiTo(const PseudoJet& jet) const
{
    return delta_phi_to(jet) * rad;
}

Angle PseudoJet::DeltaRapTo(const PseudoJet& jet) const
{
    return jet.Rap() - Rap();
}

Angle PseudoJet::Rap() const
{
    return rap() == fastjet::pseudojet_invalid_rap ? 0_rad : rap() * rad;
}

Angle PseudoJet::Phi() const
{
    return phi_std() * rad;
}

Energy PseudoJet::Energy() const
{
    return e() * GeV;
}

boca::MassSquare PseudoJet::MassSquare() const
{
    return m2() * GeV2;
}

Momentum PseudoJet::Py() const
{
    return py() * GeV;
}

Momentum PseudoJet::Pz() const
{
    return pz() * GeV;
}

Energy PseudoJet::Energy()
{
    return e() * GeV;
}

Momentum PseudoJet::Px() const
{
    return px() * GeV;
}

const PseudoJet::UserInfoBase& PseudoJet::Info() const
{
    ERROR("probably wrong user info");
    return *new UserInfoBase;
}

PseudoJet::UserInfoBase& PseudoJet::Info()
{
    ERROR("probably wrong user info");
    return *new UserInfoBase;
}

Vector2< Angle > PseudoJet::DeltaTo(const PseudoJet& jet) const
{
    return {DeltaRapTo(jet), DeltaPhiTo(jet)};
}

Vector2< Angle > PseudoJet::Angles() const
{
    return {Rap(), Phi()};
}

Vector2<Angle> PseudoJet::Angles(Vector2<Angle> const& angles) const
{
    auto phi = Phi();
    auto angles_1 = Vector2<Angle>{Rap(), phi};
    auto distance_1 = (angles - angles_1).Mod2();
    phi = Wrap(phi);
    auto angles_2 = Vector2<Angle>{Rap(), phi};
    auto distance_2 = (angles - angles_2).Mod2();
    return distance_2 < distance_1 ? angles_2 : angles_1;
}

MomentumSquare PseudoJet::ModP2() const
{
    return modp2() * GeV2;
}

Momentum PseudoJet::ModP() const
{
    return modp() * GeV;
}

LorentzVector< Momentum > PseudoJet::Vector() const
{
    return {Px(), Py(), Pz(), Energy()};
}

Vector3< Momentum > PseudoJet::Vector3() const
{
    return Vector().Vector();
}
void PseudoJet::ScaleMomentum(double factor)
{
    reset_momentum(px() * factor, py() * factor, pz() * factor, e());
}

}
