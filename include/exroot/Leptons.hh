/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "../Leptons.hh"

namespace boca
{

namespace exroot
{

/**
 * @brief PGS leptons
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
