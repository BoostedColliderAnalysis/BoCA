#pragma once

#include "BottomTagger.hh"
#include "Reader.hh"
#include "Branches.hh"
#include "PreCuts.hh"

namespace hbottomsumtagger
{


/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventBottomTagger : public analysis::BranchTagger<analysis::EventBottomTaggerBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    EventBottomTagger();

    int Train(const analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const{}

    bool TruthLevelCheck(const analysis::Jets &NewJets, const analysis::Event &event, const analysis::Tag Tag);

    int Train(const analysis::Event &event, analysis::PreCuts &precuts, const analysis::Tag tag);

    int Multiplets(const analysis::Event &event, analysis::PreCuts &precuts, const TMVA::Reader &) const;

    int GetBdt(const analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const final {
      return "EventBottom";
    }

private:

    void DefineVariables();

    analysis::Reader<analysis::BottomTagger> bottom_reader_;

};

}
