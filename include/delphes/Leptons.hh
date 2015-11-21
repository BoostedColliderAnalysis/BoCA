/**
 * Copyright (C) 2015 Jan Hajer
 */
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
  std::vector<Jet> Electrons() const final;

  std::vector<Jet> Muons() const final;

private:

    std::vector<Jet> Electrons(JetDetail jet_detail) const;

    std::vector<Jet> Muons(boca::JetDetail jet_detail) const;


};

}

}
