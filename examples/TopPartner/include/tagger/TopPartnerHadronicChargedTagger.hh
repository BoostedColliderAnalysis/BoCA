#pragma once

#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/multiplets/Quintet.hh"

namespace toppartner
{

using namespace boca;

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
