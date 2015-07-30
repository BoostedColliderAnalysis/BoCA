#pragma once

#include "Global.hh"
#include "LorentzVector.hh"
class TLorentzVector;

namespace analysis {

class Particle {

public:

    Particle() {}

    Particle(const int id);

    Particle(const Id id);

    Particle(const Id id, const int position);

    Particle(const LorentzVector& momentum, const int id, const int position);

    Particle(const TLorentzVector& momentum, const int id, const int position);

    LorentzVector momentum()const;

    int position()const;

    int id()const;

private:

    LorentzVector momentum_;

    int position_ = EmptyPosition;

    int id_;

};

}
