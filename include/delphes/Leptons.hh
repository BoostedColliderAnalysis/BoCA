#pragma once

#include "../Leptons.hh"

namespace boca {

namespace delphes {

/**
 * @brief Delphes leptons
 *
 */
class Leptons : public boca::Leptons {

public:
  boca::Jets Electrons() const final;

  boca::Jets Muons() const final;

private:

    boca::Jets Electrons(JetDetail jet_detail) const;

    boca::Jets Muons(boca::JetDetail jet_detail) const;


};

}

}
