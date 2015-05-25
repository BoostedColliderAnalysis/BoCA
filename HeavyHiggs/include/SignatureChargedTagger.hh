# pragma once

# include "Branch.hh"
# include "TopHadronicTagger.hh"
# include "ChargedHiggsSemiTagger.hh"
# include "TripletJetPairTagger.hh"
# include "Octet44.hh"

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureChargedTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    SignatureChargedTagger();

    std::vector< OctetChargedBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag){
      Print(kError,"get branches","depreciated");
      return std::vector< OctetChargedBranch >{};
    }

    int Train(analysis::Event &event, const Tag tag);

    OctetChargedBranch GetBranch(const Octet44 &octet) const;

    std::vector<Octet44> GetBdt(const std::vector< analysis::Quartet31 > &Higgsquartets, const std::vector< analysis::Quartet31 > &Jetquartets, const analysis::Reader &eventSemiReader){
      Print(kError,"get bdt","depreciated");
      return std::vector< Octet44>{};
    }

    std::vector<Octet44> Octets(analysis::Event &event, const TMVA::Reader &reader);

    analysis::ChargedHiggsSemiTagger charged_higgs_semi_tagger_;
    analysis::TripletJetPairTagger triplet_jet_pair_tagger_;

    analysis::Reader charged_higgs_semi_reader_;
    analysis::Reader triplet_jet_pair_reader_;

    TClass &Class() const {
      return *OctetChargedBranch::Class();
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureChargedTagger";
    }

private:

    void DefineVariables();

    int SaveEntries(const std::vector<Octet44> &octets) {
      for (const auto & octet : octets) static_cast<OctetChargedBranch &>(*tree_branch().NewEntry()) = GetBranch(octet);
      return octets.size();
    }

    OctetChargedBranch branch_;

};

}
