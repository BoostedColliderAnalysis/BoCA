#pragma once

#include "NewPartnerPairTagger.hh"
#include "MultipletEvent.hh"
#include "AnalysisBase.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventNewPairTagger : public TaggerTemplate<MultipletEvent<Decuplet55>,EventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<MultipletEvent<Decuplet55>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    Reader<NewPartnerPairTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
