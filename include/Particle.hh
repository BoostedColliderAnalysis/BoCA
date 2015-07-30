#pragma once

#include "Global.hh"
#include "LorentzVector.hh"
// #include "Predicate.hh"

class TLorentzVector;

namespace analysis {

class Particle {

public:

    Particle() {}

    Particle(int id);

    Particle(Id id);

    Particle(Id id, int position);

    Particle(const LorentzVector& momentum, int id, int position);

    Particle(const TLorentzVector& momentum, int id, int position);

    LorentzVector momentum() const;

    int position() const;

    int id() const;

private:

    LorentzVector momentum_;

    int position_ = EmptyPosition;

    int id_ = int(Id::empty);

};

}
