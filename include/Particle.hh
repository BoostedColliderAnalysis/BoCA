/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Particles.hh"
#include "LorentzVector.hh"

class TLorentzVector;

namespace boca {

  /**
   * @brief Position outside of a vector
   *
   */
  static int EmptyPosition = -1;

class Particle {

public:

    Particle() {}

    Particle(int id);

//     Particle(Id id);
//
    Particle(int id, int position);

    Particle(LorentzVector const& momentum, int id, int position);

    Particle(TLorentzVector const& momentum, int id, int position);

    LorentzVector momentum() const;

    int position() const;

    int id() const;

    void set(int id, int position){id_ = id; position_ = position;}

private:

    LorentzVector momentum_;

    int position_ = EmptyPosition;

    int id_ = int(Id::empty);

};

}
