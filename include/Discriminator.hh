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

    Jets GetCandidateJets(const Jets&, const float);

    Jets GetCandidateJetsForced(const Jets&, const float);

    static bool JetIsBad(fastjet::PseudoJet const& Jet);

};

}
