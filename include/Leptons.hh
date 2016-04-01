/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "FourVector.hh"
#include "multiplets/Jet.hh"

namespace boca {

/**
 * @brief calculation regarding leptons
 *
 */
class Leptons : public FourVector {

public:

    Leptons(boca::TreeReader const& tree_reader);

    virtual ~Leptons();

    std::vector<Lepton> leptons() const;

    virtual std::vector<Lepton> Electrons() const = 0;

    virtual std::vector<Lepton> Muons() const = 0;

    virtual std::vector<Lepton> Photons() const = 0;

};

}
