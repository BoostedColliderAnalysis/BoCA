#pragma once

#include "Reconstruction.hh"

namespace analysis {

/**
 * @brief Jet Discriminator
 *
 *
 */
class Discriminator : public Reconstruction {

public:

    Jets GetCandidateJets(const Jets&, const float);

    Jets GetCandidateJetsForced(const Jets&, const float);

    static bool JetIsBad(const fastjet::PseudoJet& Jet);

};

}
