#pragma once

#include "TopPartnerPairTagger.hh"
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
class EventPairTagger : public BranchTagger<EventBranch>
{

public:

    EventPairTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<MultipletEvent<Decuplet55>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "EventPair";
    }

    std::string NiceName() const final {
        return "T_{h} T_{l}";
    }
//     template <template<typename> typename Analysis>
//     void PreRequisits(Output output = Output::normal) {
//         PreRequisits<Analysis, BottomTagger>(output);
//         PreRequisits<Analysis, TopPartnerPairTagger>(output);
//     }

private:

    Reader<TopPartnerPairTagger> signature_reader_;

    Reader<BottomTagger> bottom_reader_;

};

}

}
