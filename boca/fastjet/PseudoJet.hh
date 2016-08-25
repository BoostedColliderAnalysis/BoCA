/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"
#include "boca/math/LorentzVector.hh"

class TLorentzVector;

namespace boca
{

template<typename Value_>
class LorentzVector;

/**
* @ingroup FastJet
* @brief Subclass of fastjet::PseudoJet adding BoCA related functions
*
*/
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

    boca::Mass Mass() const;

    Angle Rap() const;

    Angle Phi() const;

    Angle DeltaRTo(PseudoJet const& jet) const;

    Angle DeltaRTo(LorentzVector<Momentum> const& lorentz_vector) const;

    Angle DeltaPhiTo(PseudoJet const& jet) const;

    Angle DeltaRapTo(PseudoJet const& jet) const;

    Vector2<Angle> DeltaTo(PseudoJet const& jet) const;

    Vector2<Angle> Angles() const;

    Vector2<Angle> Angles(Vector2<Angle> const& angles) const;

    boca::MassSquare MassSquare() const;

    Momentum Px() const;

    Momentum Py() const;

    Momentum Pz() const;

    boca::Energy Energy();

    MomentumSquare ModP2() const;

    Momentum ModP() const;

    LorentzVector< Momentum > Vector() const;

    boca::Vector3<Momentum> Vector3() const;

    void ScaleMomentum(double factor);


};

}
