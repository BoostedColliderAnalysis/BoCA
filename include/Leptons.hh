/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "FourVector.hh"
#include "Jet.hh"

namespace boca {

/**
 * @brief calculation regarding leptons
 *
 */
class Leptons : public FourVector {

public:

    virtual ~Leptons();

    void NewEvent(TreeReader const& tree_reader);

    std::vector<Lepton> leptons() const;

    virtual std::vector<Lepton> Electrons() const = 0;

    virtual std::vector<Lepton> Muons() const = 0;

};

}
