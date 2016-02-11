/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "../Hadrons.hh"

namespace boca
{

/**
 * @brief exroot object extraction
 *
 */
namespace exroot
{

/**
 * @brief Pgs Jets
 *
 */
class Hadrons : public boca::Hadrons
{

public:

    Hadrons(boca::TreeReader const& tree_reader);

    std::vector<Jet> Jets() const override;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool Jets(JetDetail jet_detail);

};

}

}
