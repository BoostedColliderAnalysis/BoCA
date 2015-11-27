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

    virtual UserInfoBase const& Info() const = 0;

    virtual UserInfoBase& Info() = 0;

    Momentum Pt() const;

    boca::Energy Energy() const;

    boca::Mass Mass()const;

    Angle Rap() const;

    Angle Phi() const;

    Angle DeltaRTo(fastjet::PseudoJet const& jet) const;

    Angle DeltaPhiTo(fastjet::PseudoJet const& jet) const;

};

}
