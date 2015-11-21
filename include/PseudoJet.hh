/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"
#include "Units.hh"
#include "JetInfo.hh"

class TLorentzVector;

namespace boca
{

class PseudoJet : public fastjet::PseudoJet
{
public:

    using fastjet::PseudoJet::PseudoJet;

    PseudoJet();

    PseudoJet(TLorentzVector const& vector);

    PseudoJet(LorentzVector const& vector);

    PseudoJet(exroot::Electron const& Particle);

    PseudoJet(exroot::GenJet const& Particle);

    PseudoJet(exroot::GenParticle const& Particle);

    PseudoJet(exroot::Jet const& Particle);

    PseudoJet(exroot::LHEFParticle const& Particle);

    PseudoJet(exroot::Muon const& Particle);

    PseudoJet(exroot::Photon const& Particle);

    PseudoJet(exroot::Tau const& Particle);

    virtual UserInfoBase const& Info() const = 0;

    virtual UserInfoBase& Info() = 0;

    Momentum Pt() const;

    boca::Mass Mass()const;

    Angle DeltaRTo(PseudoJet const& jet) const;

};

}
