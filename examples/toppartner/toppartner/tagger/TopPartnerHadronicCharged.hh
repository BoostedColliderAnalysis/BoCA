#pragma once

#include "boca/multiplets/Quintet.hh"

#include "standardmodel/tagger/TopHadronic.hh"

namespace toppartner
{

using namespace boca;

namespace tagger
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerHadronicCharged : public standardmodel::tagger::TopHadronic
{

public:

    TopPartnerHadronicCharged();

    std::string Name() const override;

    latex::String LatexName() const override;

private:


};

}

}
