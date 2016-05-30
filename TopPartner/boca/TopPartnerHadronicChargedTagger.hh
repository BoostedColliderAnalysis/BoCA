#pragma once

#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/multiplets/Quintet.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerHadronicChargedTagger : public standardmodel::tagger::TopHadronic
{

public:

    TopPartnerHadronicChargedTagger();

    std::string Name() const override;

    latex::String LatexName() const override;

private:


};

}

}
