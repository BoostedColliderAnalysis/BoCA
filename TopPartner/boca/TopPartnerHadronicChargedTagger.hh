#pragma once

#include "boca/standardmodel/TopHadronicTagger.hh"
#include "boca/multiplets/Quintet.hh"

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

    latex::String LatexName() const override;

private:


};

}

}
