/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Identification.hh"
#include "Vector2.hh"
#include "fastjet/PseudoJet.hh"
#include "Units.hh"

namespace boca {

class MultipletBase : public Identification {

public:

  virtual MultipletBase const& singlet() const = 0;

  virtual fastjet::PseudoJet Jet() const = 0;

  virtual Vector2 Pull() const = 0;

  virtual float Ht() const = 0;

  virtual int Charge() const = 0;

  virtual float BottomBdt() const = 0;

  boca::Mass Mass() const {
    return Jet().m() * GeV;
  }

  Momentum Pt() const {
    return Jet().pt() * GeV;
  }

  Angle Rap() const {
    if (Jet().rap() == fastjet::pseudojet_invalid_rap) return 0. * rad;
    if (Jet().rap() > 100) return 0. * rad;
    return Jet().rap() * rad;
  }

  Angle Phi() const {
    return Jet().phi_std() * rad;
  }

  Angle DeltaRTo(fastjet::PseudoJet const& jet) const {
    return Jet().delta_R(jet) * rad;
  }

  /**
   * @brief calculate Reference vector for other - this
   * @return Vector2 reference vector
   *
   */
  Vector2 Reference(fastjet::PseudoJet const& jet) const
  {
    return Vector2(jet.rap() - Jet().rap(), Jet().delta_phi_to(jet));
  }

};

}
