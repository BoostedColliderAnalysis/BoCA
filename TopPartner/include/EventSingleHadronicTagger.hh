/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "SignatureSingleHadronicTagger.hh"
#include "MultipletEvent.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleHadronicTagger : public BranchTagger<EventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "EventSingleHadronic";
    }

private:

    Reader<SignatureSingleHadronicTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}