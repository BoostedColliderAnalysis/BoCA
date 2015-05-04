# pragma once
# include "HTriplet.hh"
# include "HBottomTagger.hh"
# include "HWTagger.hh"
# include "HBranchTopTagger.hh"

// #include "fastjet/contrib/MeasureFunction.hh"

/**
 * @brief Hadronic top BDT tagger
 *
 */
class HTopHadronTagger : public hanalysis::HMva
{

public:

    HTopHadronTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger);

    std::vector<HTopHadronBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag, float pre_cut = 0);

    std::vector<hanalysis::HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::HReader & TopHadronicReader);

    hanalysis::HTriplet GetBdt(hanalysis::HTriplet &Triplet, const hanalysis::HReader &TopHadronicReader);

    std::vector<hanalysis::HTriplet> GetBdt(const HJets &Jets, const HJets &Leptons, const hanalysis::HReader &TopHadronicReader, hanalysis::HWTagger &WTagger, hanalysis::HReader &WReader, hanalysis::HBottomTagger &BottomTagger, hanalysis::HReader &BottomReader);


    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HTopHadronBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWTagger WTagger;

    hanalysis::HReader  BottomReader;
    hanalysis::HReader  WReader;

    HTopHadronBranch GetBranch(const hanalysis::HTriplet &triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronTagger";
    };

private:

    void DefineVariables();

    HTag GetTag(const hanalysis::HTriplet &);

    HTag GetTag(const fastjet::PseudoJet& Jet);

    void GetBottomInfo(HTopHadronBranch &TopHadronicBranch, const fastjet::PseudoJet jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTopHadronBranch Branch;
    hanalysis::HJetTag JetTag;

    float TopWindow ;
    float WMassWindow ;


    void NSubJettiness(hanalysis::HTriplet& triplet);
    SubJettiness NSubJettiness(const fastjet::PseudoJet & jet);

};

