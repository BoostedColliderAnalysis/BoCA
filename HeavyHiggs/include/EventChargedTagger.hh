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

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger, const analysis::HChargedJetPairTagger &NewChargedJetPairTagger, const analysis::WSemiTagger &Neww_semi_tagger, const analysis::WHadronicTagger &NewWTagger, const analysis::TopSemiTagger &Newtop_semi_tagger, const analysis::TopHadronicTagger &Newtop_hadronic_tagger, const analysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger, const SignatureChargedTagger &NewChargedSignatureTagger);


    std::vector< EventChargedBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    EventChargedBranch GetBranch(const analysis::MultipletEvent<Octet44> &event) const;

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);


    std::vector<analysis::MultipletEvent<Octet44>> GetBdt(const std::vector< Octet44 > &octets, Jets &jets, const Jets &SubJets, Jets &Leptons, analysis::GlobalObservables &global_observables, const analysis::Reader &eventSemiReader);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);


    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    analysis::HChargedJetPairTagger ChargedJetPairTagger;
    SignatureChargedTagger SignatureSemiTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader ChargedHiggsSemiReader;
    analysis::Reader ChargedJetPairReader;
    analysis::Reader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventChargedTagger";
    }

private:

    void DefineVariables();

    EventChargedBranch Branch;

};

}
