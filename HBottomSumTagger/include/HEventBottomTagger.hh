#pragma once

#include "BottomTagger.hh"
#include "Reader.hh"
#include "Branches.hh"
#include "PreCuts.hh"

namespace hbottomsumtagger {


/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventBottomTagger : public analysis::BranchTagger<analysis::EventBottomTaggerBranch> {

public:

    /**
    * @brief Constructor
    *
    */
    EventBottomTagger();

    int Train(const analysis::Event&, const analysis::PreCuts&, const analysis::Tag) const
    {
        return 1;
    }

    bool TruthLevelCheck(const analysis::Jets& NewJets, const analysis::Event& event, analysis::Tag tag);

    int Train(const analysis::Event& event, const analysis::PreCuts& precuts, analysis::Tag tag);

    std::vector<analysis::EventBranch> Multiplets(const analysis::Event& event, const analysis::PreCuts&, const TMVA::Reader&) const;

    int GetBdt(const analysis::Event&, const analysis::PreCuts&, const TMVA::Reader&) const
    {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
        return 1;
    }

    std::string Name() const final
    {
        return "EventBottom";
    }

private:

    void DefineVariables();
    void branch();

    analysis::Reader<analysis::BottomTagger> bottom_reader_;

};

}
