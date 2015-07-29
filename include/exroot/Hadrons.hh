#pragma once

#include "../Hadrons.hh"

namespace analysis {

namespace exroot {

/**
 * @brief Pgs Jets
 *
 */
class Hadrons : public analysis::Hadrons {

public:
  analysis::Jets Jets() const final override;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool Jets(JetDetail jet_detail);

};

}

}
