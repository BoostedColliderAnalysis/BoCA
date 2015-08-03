#pragma once
#include "Identification.hh"
#include "Vector2.hh"
#include "fastjet/PseudoJet.hh"

namespace analysis {

class MultipletBase : public Identification {

public:

  virtual const MultipletBase& singlet() const = 0;

  virtual fastjet::PseudoJet Jet() const = 0;

  virtual Vector2 Pull() const = 0;

  virtual float Ht() const = 0;

  virtual int Charge() const = 0;

  /**
   * @brief calculate Reference vector for other - this
   * @return Vector2 reference vector
   *
   */
  Vector2 Reference(const fastjet::PseudoJet& vector) const
  {
    return Vector2(vector.rap() - Jet().rap(), Jet().delta_phi_to(vector));
  }

};

}
