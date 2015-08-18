#pragma once

#include "../Hadrons.hh"

namespace boca {

namespace exroot {

/**
 * @brief Pgs Jets
 *
 */
class Hadrons : public boca::Hadrons {

public:
  boca::Jets Jets() const final;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool Jets(JetDetail jet_detail);

};

}

}
