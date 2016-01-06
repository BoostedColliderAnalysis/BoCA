/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "../Leptons.hh"

namespace boca
{

namespace delphes
{

/**
 * @brief Delphes leptons
 *
 */
class Leptons : public boca::Leptons
{

public:

    Leptons(boca::TreeReader const& tree_reader);

    std::vector<Lepton> Electrons() const final;

    std::vector<Lepton> Muons() const final;

    std::vector<Lepton> Photons() const final;

};

}

}
