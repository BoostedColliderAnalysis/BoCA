# pragma once

# include "Branch.hh"
# include "HeavyHiggsSemiTagger.hh"
# include "JetPairTagger.hh"
# include "MultipletEvent.hh"

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusionTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventFusionTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector< analysis::MultipletEvent<analysis::Sextet> > Events(analysis::Event& event, TMVA::Reader& eventSemiReader);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventFusionBranch GetBranch(const analysis::MultipletEvent<analysis::Sextet> &event) const;

    analysis::BottomTagger bottom_tagger_;
//     analysis::WSemiTagger w_semi_tagger;
//     analysis::WHadronicTagger WTagger;
//     analysis::TopSemiTagger top_semi_tagger;
//     analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HeavyHiggsSemiTagger heavy_higgs_semi_tagger_;

    analysis::Reader bottom_reader_;
//     analysis::Reader WSemiReader;
//     analysis::Reader WReader;
//     analysis::Reader TopHadronicReader;
//     analysis::Reader TopSemiReader;
    analysis::Reader heavy_higgs_semi_reader_;

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventFusionTagger";
    }

private:

    void DefineVariables();


    int SaveEntries(const std::vector<analysis::MultipletEvent<analysis::Sextet>> &events) {
      for (const auto & event : events) static_cast<EventFusionBranch &>(*tree_branch().NewEntry()) = GetBranch(event);
      return events.size();
    }

    int SaveEntry(const analysis::MultipletEvent<analysis::Sextet> &event) {
      static_cast<EventFusionBranch &>(*tree_branch().NewEntry()) = GetBranch(event);
      return 1;
    }

    std::vector<analysis::MultipletEvent<analysis::Sextet>> GetHeavyHiggsevents(Jets &jets);

    EventFusionBranch branch_;

};

}
