# pragma once


# include "HDoublet.hh"
# include "HBottomTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HTopLeptonTagger : public hanalysis::HMva
{

public:

    HTopLeptonTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger);

    std::vector<HTopLeptonBranch> GetBranches(hanalysis::HEvent &Event, const HObject::HTag State);

    std::vector<hanalysis::HDoublet> GetBdt(const HJets &Jets, const HJets &Leptons, const hanalysis::HReader &Reader);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry) {
        return static_cast<HTopLeptonBranch &>(*EventClonesArray.At(Entry)).Bdt;
    }

    HTopLeptonBranch GetBranch(const hanalysis::HDoublet &Doublet) const;

    hanalysis::HBottomTagger BottomTagger;

    hanalysis::HReader BottomReader;
protected:

    virtual inline std::string ClassName() const {
        return "HTopLeptonTagger";
    };

private:

    void DefineVariables();

    HTopLeptonBranch Branch;

    float TopWindow;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    int TopJetNumberNumber = 0;
    int TopQuarkNumber = 0;
    int LeptonJetNumber = 0;
    int LeptonNumber = 0;
    int EventNumber = 0;

};
