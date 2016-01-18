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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Decuplet55>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string LatexName() const final;

private:

    Reader<NewPartnerPairTagger> signature_reader_;

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}

}
