#pragma once

#include "TopLeptonicTagger.hh"
#include "multiplets/Quintet.hh"

namespace boca
{

namespace naturalness
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

    std::string LatexName() const override;

private:


};

}

}
