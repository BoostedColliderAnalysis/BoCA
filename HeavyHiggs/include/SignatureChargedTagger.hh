# pragma once

# include "Branch.hh"
# include "TopHadronicTagger.hh"
# include "HChargedHiggsSemiTagger.hh"
# include "HChargedJetPairTagger.hh"
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

    void SetTagger(
      const analysis::BottomTagger &NewBottomTagger,
      const analysis::HChargedJetPairTagger &NewChargedJetPairTagger,
      const analysis::WSemiTagger &Neww_semi_tagger,
      const analysis::WHadronicTagger &NewWTagger,
      const analysis::TopSemiTagger &Newtop_semi_tagger,
      const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
      const analysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger);


    std::vector< OctetChargedBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    OctetChargedBranch GetBranch(const Octet44 &octet) const;

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);


    std::vector<Octet44> GetBdt(
        const std::vector< analysis::Quartet31 > &Higgsquartets, const std::vector< analysis::Quartet31 > &Jetquartets, const analysis::Reader &eventSemiReader);


    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    analysis::HChargedJetPairTagger ChargedJetPairTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader ChargedHiggsSemiReader;
    analysis::Reader ChargedJetPairReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureChargedTagger";
    }

private:

    void DefineVariables();

    OctetChargedBranch Branch;

};

}
