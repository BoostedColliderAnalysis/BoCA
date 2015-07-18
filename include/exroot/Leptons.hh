#pragma once

#include "../Leptons.hh"

namespace analysis {

namespace exroot {

/**
 * @brief PGS leptons
 *
 */
class Leptons : public analysis::Leptons {

public:

    analysis::Jets Electrons() const final;

    analysis::Jets Muons() const final;

};

}

}
