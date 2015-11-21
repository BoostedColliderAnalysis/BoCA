/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "PseudoJet.hh"
#include "TLorentzVector.h"
#include "Particles.hh"
#include "Debug.hh"

namespace boca
{

PseudoJet::PseudoJet() : fastjet::PseudoJet() {}

PseudoJet::PseudoJet(TLorentzVector const& vector) : fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E()){}

PseudoJet::PseudoJet(LorentzVector const& vector) : fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E()) {}

PseudoJet::PseudoJet(const exroot::Electron& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::GenJet& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::GenParticle& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Jet& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::LHEFParticle& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Muon& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Photon& Particle) : PseudoJet(LorentzVector(Particle)) {}

PseudoJet::PseudoJet(const exroot::Tau& Particle) : PseudoJet(LorentzVector(Particle)) {}

Momentum PseudoJet::Pt() const
{
    return pt() * GeV;
}

Mass PseudoJet::Mass() const
{
    return m() * GeV;
}
Angle PseudoJet::DeltaRTo(const PseudoJet& jet) const
{
    return this->delta_R(jet) * rad;
}

}

