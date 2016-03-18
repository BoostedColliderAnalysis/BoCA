#pragma once

#include "TopHadronicTagger.hh"
#include "multiplets/Quintet.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerHadronicChargedTagger : public standardmodel::TopHadronicTagger
{

public:

    TopPartnerHadronicChargedTagger();

    std::string Name() const override;

    std::string LatexName() const override;

private:


};

}

}
