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
    INFO0;
}

PseudoJet::PseudoJet(fastjet::PseudoJet const& pseudo_jet) :
    fastjet::PseudoJet(pseudo_jet)
{
    INFO(pseudo_jet.px(), px(), pseudo_jet.py(), py());
}

PseudoJet::PseudoJet(TLorentzVector const& vector) :
    fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E())
{
    INFO(vector.Px(), px(), vector.Py(), py());
}

PseudoJet::PseudoJet(boca::LorentzVector<Momentum> const& vector) :
    fastjet::PseudoJet(vector.Px() / GeV, vector.Py() / GeV, vector.Pz() / GeV, vector.E() / GeV)
{
    INFO0;
}

PseudoJet::PseudoJet(boca::Vector3<Momentum> const& spatial, boca::Energy const& e) :
    fastjet:: PseudoJet(spatial.X() / GeV, spatial.Y() / GeV, spatial.Z() / GeV, e / GeV)
{
    INFO0;
}

PseudoJet::PseudoJet(Vector2<Momentum> const& transverse, Momentum const& z, boca::Energy const& e) :
    fastjet:: PseudoJet(transverse.X() / GeV, transverse.Y() / GeV, z / GeV, e / GeV)
{
    INFO0;
}

PseudoJet::PseudoJet(Momentum const& x, Momentum const& y, Momentum const& z, boca::Energy const& e) :
    fastjet:: PseudoJet(x / GeV, y / GeV, z / GeV, e / GeV)
{
    INFO0;
}

void PseudoJet::ScaleMomentum(double factor)
{
    reset_momentum(px() * factor, py() * factor, pz() * factor, e());
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

boca::LorentzVector< Momentum > PseudoJet::LorentzVector() const
{
    return {Px(), Py(), Pz(), Energy()};
}

Vector3< Momentum > PseudoJet::Spatial() const
{
    return {Px(), Py(), Pz()};
}

fastjet::PseudoJet& PseudoJet::FastJet()
{
    return static_cast<fastjet::PseudoJet&>(*this);
}

fastjet::PseudoJet const& PseudoJet::FastJet() const
{
    return static_cast<fastjet::PseudoJet const&>(*this);
}

Momentum PseudoJet::Pt() const
{
    return pt() * GeV;
}

Mass PseudoJet::Mass() const
{
    return m() > 0 ? m() * GeV : massless;
}

Energy PseudoJet::Energy() const
{
    return e() * GeV;
}

Energy PseudoJet::E() const
{
    return e() * GeV;
}

Energy PseudoJet::Et2() const
{
    return fastjet::PseudoJet::Et2() * GeV;
}

Energy PseudoJet::Et() const
{
    return fastjet::PseudoJet::Et() * GeV;
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

Momentum PseudoJet::Px() const
{
    return px() * GeV;
}

MomentumSquare PseudoJet::ModP2() const
{
    return modp2() * GeV2;
}

Momentum PseudoJet::ModP() const
{
    return modp() * GeV;
}

Angle PseudoJet::Phi() const
{
    return phi_std() * rad;
}

Angle PseudoJet::Rap() const
{
    return rap() == fastjet::pseudojet_invalid_rap ? 0_rad : rap() * rad;
}

Angle PseudoJet::DeltaPhiTo(PseudoJet const& jet) const
{
    return delta_phi_to(jet) * rad;
}

Angle PseudoJet::DeltaRapTo(PseudoJet const& jet) const
{
    return jet.Rap() - Rap();
}

Angle PseudoJet::DeltaRTo(PseudoJet const& jet) const
{
    auto delta_r = delta_R(jet);
    return delta_r == fastjet::pseudojet_invalid_rap || delta_r > 100 ? 0_rad : delta_r * rad;
}

Vector2< Angle > PseudoJet::DeltaTo(PseudoJet const& jet) const
{
    return {DeltaRapTo(jet), DeltaPhiTo(jet)};
}

Vector2< Angle > PseudoJet::Angles(bool wrap_phi) const
{
    return {Rap(), wrap_phi ? Wrap(Phi()) : Phi()};
}

Vector2<Angle> PseudoJet::AnglesMinTo(PseudoJet const& jet) const
{
    auto angles = jet.Angles();
    auto angles_1 = Angles(false);
    auto angles_2 = Angles(true);
    return angles - angles_1 < angles - angles_2  ?  angles_1 : angles_2;
}

Vector2<Momentum> PseudoJet::Transverse() const
{
    return {Px(), Py()};
}

bool PseudoJet::operator<(const boca::PseudoJet &jet) const
{
    return Pt() < jet.Pt();
}

bool PseudoJet::operator==(boca::PseudoJet const& pseudo_jet) const
{
    return FastJet() == pseudo_jet.FastJet();
}

std::ostream & operator<<(std::ostream & stream, PseudoJet const& jet)
{
    stream << Stream(jet.Px()) << Stream(jet.Py()) << Stream(jet.Pz()) << Stream(jet.E());
    return stream;
}

bool PseudoJet::HasInfo()
{
    return FastJet().has_user_info();
}


void PseudoJet::Reset(const boca::PseudoJet &pseudo_jet)
{
    reset(pseudo_jet.FastJet());
}

}
