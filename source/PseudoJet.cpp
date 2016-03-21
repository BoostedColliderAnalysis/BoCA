/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "PseudoJet.hh"
#include "TLorentzVector.h"
#include "physics/Particles.hh"
#include "Jet.hh"
// #define DEBUGGING
#include "DEBUG.hh"

namespace boca
{

PseudoJet::PseudoJet() :
    fastjet::PseudoJet()
{}

PseudoJet::PseudoJet(TLorentzVector const& vector) :
    fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E())
{
    DEBUG(vector.Px(), px(), vector.Py(), py());
}

PseudoJet::PseudoJet(LorentzVector<Momentum> const& vector) :
    fastjet::PseudoJet(vector.Px() / GeV, vector.Py() / GeV, vector.Pz() / GeV, vector.E() / GeV)
{}

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
    return delta_R(jet) == fastjet::pseudojet_invalid_rap ? 0_rad : delta_R(jet) * rad;
}

Angle PseudoJet::DeltaRTo(LorentzVector< Momentum > const& lorentz_vector) const
{
    fastjet::PseudoJet jet(lorentz_vector.X() / GeV, lorentz_vector.Y() / GeV, lorentz_vector.Z() / GeV, lorentz_vector.T() / GeV);
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
  Angle phi = Phi();
  Vector2<Angle> angles_1(Rap(), phi);
  auto distance_1 = (angles - angles_1).Mod2();
  phi = Wrap(phi);
  Vector2<Angle> angles_2(Rap(), phi);
  auto distance_2 = (angles - angles_2).Mod2();
  return distance_2 < distance_1 ? angles_2 : angles_1;
}

}
