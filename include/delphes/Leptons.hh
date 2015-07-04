#pragma once

#include "../Leptons.hh"

namespace analysis
{

namespace delphes
{

/**
 * @brief Delphes leptons
 *
 */
class Leptons : public analysis::Leptons
{

public:

    analysis::Jets Electrons() const;

    analysis::Jets Muons() const;

private:

    analysis::Jets Electrons(JetDetail jet_detail) const;

    analysis::Jets Muons(analysis::JetDetail jet_detail) const;


};

}

}
