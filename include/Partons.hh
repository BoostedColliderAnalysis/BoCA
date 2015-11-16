/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "FourVector.hh"

namespace boca {

/**
 * @brief particles for HAnalysis
 *
 */
class Partons : public FourVector {

public:

    virtual ~Partons() {};

    void NewEvent(const TreeReader& tree_reader);

    virtual Jets Particles() const = 0;

    virtual Jets GenParticles() const = 0;

};

}
