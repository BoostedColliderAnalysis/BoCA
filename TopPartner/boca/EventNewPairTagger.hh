#pragma once

#include "boca/NewPartnerPairTagger.hh"
#include "boca/MultipletEvent.hh"
#include "boca/analysis/AnalysisBase.hh"

namespace boca
{

namespace toppartner
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventNewPairTagger : public Tagger<MultipletEvent<Decuplet55>,EventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<MultipletEvent<Decuplet55>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    Reader<NewPartnerPairTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
