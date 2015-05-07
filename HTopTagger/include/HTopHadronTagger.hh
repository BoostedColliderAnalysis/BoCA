# pragma once
# include "HTriplet.hh"
# include "BottomTagger.hh"
# include "HWHadronicTagger.hh"
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

    void SetTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::HWHadronicTagger &NewWTagger);

    std::vector<HTopHadronBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, float pre_cut = 0);

    std::vector<hanalysis::HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const HJets &Jets, const hanalysis::Reader & TopHadronicReader);

    hanalysis::HTriplet GetBdt(hanalysis::HTriplet &Triplet, const hanalysis::Reader &TopHadronicReader);

    std::vector<hanalysis::HTriplet> GetBdt(const HJets &Jets, const HJets &Leptons, const hanalysis::Reader &TopHadronicReader, hanalysis::HWHadronicTagger &WTagger, hanalysis::Reader &WReader, hanalysis::BottomTagger &BottomTagger, hanalysis::Reader &BottomReader);


    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HTopHadronBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWHadronicTagger WTagger;

    hanalysis::Reader  BottomReader;
    hanalysis::Reader  WReader;

    HTopHadronBranch GetBranch(const hanalysis::HTriplet &triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const hanalysis::HTriplet &);

    Tag GetTag(const fastjet::PseudoJet& Jet);

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

