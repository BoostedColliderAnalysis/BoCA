#pragma once

#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Quintet.hh"

namespace toppartner
{

using namespace boca;


namespace tagger
{
/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerLeptonicCharged : public standardmodel::tagger::TopLeptonic
{

public:

    TopPartnerLeptonicCharged();

    std::string Name() const override;

    latex::String LatexName() const override;

private:


};

}

}
