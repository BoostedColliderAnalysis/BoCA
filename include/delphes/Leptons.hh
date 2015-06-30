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

    Leptons();

    analysis::Jets Electrons();

    analysis::Jets Muons();

private:

    analysis::Jets Electrons(JetDetail jet_detail);

    analysis::Jets Muons(JetDetail jet_detail);


};

}

}
