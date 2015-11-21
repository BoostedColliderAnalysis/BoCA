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
    std::vector<Jet> Jets() const final;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool Jets(JetDetail jet_detail);

};

}

}
