#pragma once

#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/multiplets/Quintet.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerLeptonicChargedTagger : public standardmodel::TopLeptonicTagger
{

public:

    TopPartnerLeptonicChargedTagger();

    std::string Name() const override;

    latex::String LatexName() const override;

private:


};

}

}
