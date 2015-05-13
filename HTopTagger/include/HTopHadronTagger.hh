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
class HTopHadronTagger : public hanalysis::Tagger
{

public:

    HTopHadronTagger();

    void SetTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::WHadronicTagger &NewWTagger);

    std::vector<HTopHadronBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, float pre_cut = 0);

    std::vector<hanalysis::Triplet>  GetBdt(const std::vector< hanalysis::Doublet > &doublets, const Jets &jets, const hanalysis::Reader & TopHadronicReader);

    hanalysis::Triplet GetBdt(hanalysis::Triplet &triplet, const hanalysis::Reader &TopHadronicReader);

    std::vector<hanalysis::Triplet> GetBdt(const Jets &jets, const Jets &Leptons, const hanalysis::Reader &TopHadronicReader, hanalysis::WHadronicTagger &WTagger, hanalysis::Reader &WReader, hanalysis::BottomTagger &BottomTagger, hanalysis::Reader &BottomReader);


    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HTopHadronBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::WHadronicTagger WTagger;

    hanalysis::Reader  BottomReader;
    hanalysis::Reader  WReader;

    HTopHadronBranch GetBranch(const hanalysis::Triplet &triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const hanalysis::Triplet &);

    Tag GetTag(const fastjet::PseudoJet& Jet);

    void GetBottomInfo(HTopHadronBranch &top_hadronic_branch, const fastjet::PseudoJet jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTopHadronBranch Branch;
    hanalysis::HJetTag JetTag;

    float TopWindow ;
    float WMassWindow ;


    void NSubJettiness(hanalysis::Triplet& triplet);
    SubJettiness NSubJettiness(const fastjet::PseudoJet & jet);

};

