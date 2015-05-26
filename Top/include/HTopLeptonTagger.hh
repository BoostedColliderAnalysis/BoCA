# pragma once


# include "Doublet.hh"
# include "BottomTagger.hh"
# include "Reader.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HTopLeptonTagger : public analysis::Tagger
{

public:

    HTopLeptonTagger();

    void SetTagger(const analysis::BottomTagger &NewBottomTagger);

    std::vector<analysis::HTopLeptonBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag tag);

    std::vector<analysis::Doublet> GetBdt(const Jets &jets, const Jets &Leptons, const analysis::Reader &Reader);

    analysis::HTopLeptonBranch GetBranch(const analysis::Doublet &doublet) const;

    analysis::BottomTagger bottom_tagger_;

    analysis::Reader BottomReader;
protected:

    virtual inline std::string ClassName() const {
        return "HTopLeptonTagger";
    };

private:

    void DefineVariables();

    analysis::HTopLeptonBranch Branch;

    float TopWindow;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    int TopJetNumberNumber = 0;
    int TopQuarkNumber = 0;
    int LeptonJetNumber = 0;
    int LeptonNumber = 0;
    int eventNumber = 0;

};
