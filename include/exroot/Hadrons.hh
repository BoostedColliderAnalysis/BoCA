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

    analysis::Jets Jets() const final;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool Jets(const JetDetail jet_detail);

};

}

}
