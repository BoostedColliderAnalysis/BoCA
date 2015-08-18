#pragma once

#include "../Leptons.hh"

namespace boca {

namespace exroot {

/**
 * @brief PGS leptons
 *
 */
class Leptons : public boca::Leptons {

public:
  boca::Jets Electrons() const final;

  boca::Jets Muons() const final;
};

}

}
