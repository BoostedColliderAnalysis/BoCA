/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Reconstruction.hh"

namespace boca {

/**
 * @brief Jet Discriminator
 *
 *
 */
class Discriminator : public Reconstruction {

public:

   std::vector<Jet> GetCandidateJets(std::vector<Jet> const&, const float);

   std::vector<Jet> GetCandidateJetsForced(std::vector<Jet> const&, const float);

    static bool JetIsBad(Jet const& Jet);

};

}
