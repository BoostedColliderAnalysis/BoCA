#pragma once
#include "Identification.hh"
#include "Vector2.hh"
#include "fastjet/PseudoJet.hh"

namespace analysis {

class Object : public Identification {

public:

  virtual fastjet::PseudoJet Jet() const = 0;

  virtual fastjet::PseudoJet Jet(Structure) const = 0;

  virtual float Ht() const = 0;

  virtual const Object& singlet() const = 0;

  virtual Vector2 Pull() const = 0;

  virtual Vector2 Reference(const fastjet::PseudoJet& vector) const = 0;

};

}
