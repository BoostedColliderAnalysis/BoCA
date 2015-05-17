# pragma once
# include "Triplet.hh"
# include "BottomTagger.hh"
# include "WHadronicTagger.hh"
# include "HBranchTopTagger.hh"

// #include "fastjet/contrib/MeasureFunction.hh"

/**
 * @brief Hadronic top BDT tagger
 *
 */
class HTopHadronTagger : public analysis::Tagger
{

public:

    HTopHadronTagger();

    void SetTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::WHadronicTagger &NewWTagger);

    std::vector<HTopHadronBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag, float pre_cut = 0);

    std::vector<analysis::Triplet>  GetBdt(const std::vector< analysis::Doublet > &doublets, const Jets &jets, const analysis::Reader & TopHadronicReader);

    analysis::Triplet GetBdt(analysis::Triplet &triplet, const analysis::Reader &TopHadronicReader);

    std::vector<analysis::Triplet> GetBdt(const Jets &jets, const Jets &Leptons, const analysis::Reader &TopHadronicReader, analysis::WHadronicTagger &WTagger, analysis::Reader &WReader, analysis::BottomTagger &BottomTagger, analysis::Reader &BottomReader);


    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry){
      return ((HTopHadronBranch *) eventClonesArray.At(Entry))->Bdt;
    }

    analysis::BottomTagger bottom_tagger_;
    analysis::WHadronicTagger WTagger;

    analysis::Reader  BottomReader;
    analysis::Reader  WReader;

    HTopHadronBranch GetBranch(const analysis::Triplet &triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const analysis::Triplet &);

    Tag GetTag(const fastjet::PseudoJet& Jet);

    void GetBottomInfo(HTopHadronBranch &top_hadronic_branch, const fastjet::PseudoJet jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTopHadronBranch Branch;
    analysis::HJetTag JetTag;

    float TopWindow ;
    float WMassWindow ;


    void NSubJettiness(analysis::Triplet& triplet);
    SubJettiness NSubJettiness(const fastjet::PseudoJet & jet);

};

