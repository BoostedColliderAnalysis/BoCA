# pragma once


# include "HDoublet.hh"
# include "BottomTagger.hh"
# include "Reader.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HTopLeptonTagger : public hanalysis::Tagger
{

public:

    HTopLeptonTagger();

    void SetTagger(const hanalysis::BottomTagger &NewBottomTagger);

    std::vector<HTopLeptonBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag tag);

    std::vector<hanalysis::HDoublet> GetBdt(const Jets &jets, const Jets &Leptons, const hanalysis::Reader &Reader);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry) {
        return static_cast<HTopLeptonBranch &>(*EventClonesArray.At(Entry)).Bdt;
    }

    HTopLeptonBranch GetBranch(const hanalysis::HDoublet &Doublet) const;

    hanalysis::BottomTagger bottom_tagger_;

    hanalysis::Reader BottomReader;
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
