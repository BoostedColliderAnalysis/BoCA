/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"
#include "physics/LorentzVector.hh"

class TLorentzVector;

namespace boca
{

class PseudoJet : public fastjet::PseudoJet
{
public:

    using fastjet::PseudoJet::PseudoJet;

    PseudoJet();

    PseudoJet(TLorentzVector const& vector);

    PseudoJet(LorentzVector<Momentum> const& vector);

    virtual UserInfoBase const& Info() const;

    virtual UserInfoBase& Info();

    Momentum Pt() const;

    boca::Energy Energy() const;

    boca::Mass Mass()const;

    Angle Rap() const;

    Angle Phi() const;

    Angle DeltaRTo(fastjet::PseudoJet const& jet) const;

    Angle DeltaRTo(LorentzVector<Momentum> const& lorentz_vector) const;

    Angle DeltaPhiTo(fastjet::PseudoJet const& jet) const;

    boca::MassSquare MassSquare() const;

    Momentum Px() const;

    Momentum Py() const;

    Momentum Pz() const;

    boca::Energy Energy();

};

}
