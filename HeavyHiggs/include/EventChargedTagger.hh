# pragma once

# include "MultipletEvent.hh"
# include "SignatureChargedTagger.hh"

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventChargedTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventChargedTagger();

    std::vector< EventChargedBranch > GetBranches(analysis::Event &, const Tag){
      Print(kError,"get branches","depreciated");
      return std::vector< EventChargedBranch >{};
    }

    int Train(analysis::Event &event, const Tag tag);

    EventChargedBranch GetBranch(const analysis::MultipletEvent<Octet44> &event) const;

    std::vector<analysis::MultipletEvent<Octet44>> GetBdt(analysis::Event& event, const std::vector< Octet44 >& octets, Jets& jets, const Jets& SubJets, Jets& Leptons, analysis::GlobalObservables& global_observables, const analysis::Reader& eventSemiReader){
      Print(kError,"get bdt","depreciated");
      return std::vector<analysis::MultipletEvent<Octet44>>{};
    }


//     analysis::GlobalObservables global_observables(analysis::Event &event);


    std::vector<analysis::MultipletEvent<Octet44>> Events(analysis::Event& event, const TMVA::Reader& reader);

    float ReadBdt(const TClonesArray& clones_array, const int entry);


    analysis::BottomTagger bottom_tagger_;
//     analysis::WSemiTagger w_semi_tagger;
//     analysis::WHadronicTagger WTagger;
//     analysis::TopSemiTagger top_semi_tagger;
//     analysis::TopHadronicTagger top_hadronic_tagger;
//     analysis::ChargedHiggsSemiTagger charged_higgs_semi_tagger;
//     analysis::TripletJetPairTagger Chargedjet_pair_tagger;
    SignatureChargedTagger signature_semi_tagger_;

    analysis::Reader bottom_reader_;
//     analysis::Reader WSemiReader;
//     analysis::Reader WReader;
//     analysis::Reader TopHadronicReader;
//     analysis::Reader TopSemiReader;
//     analysis::Reader ChargedHiggsSemiReader;
//     analysis::Reader ChargedJetPairReader;
    analysis::Reader signature_semi_reader_;


    TClass &Class() const {
      return *EventChargedBranch::Class();
    }


protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventChargedTagger";
    }

private:


  void DefineVariables();

  int SaveEntries(const std::vector<analysis::MultipletEvent<Octet44>> &events) {
    for (const auto & event : events) static_cast<EventChargedBranch &>(*tree_branch().NewEntry()) = GetBranch(event);
    return events.size();
  }


    EventChargedBranch branch_;

};

}
