# pragma once

# include "Doublet.hh"
# include "BottomTagger.hh"
# include "Reader.hh"

namespace analysis
{

namespace top
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HTopLeptonTagger : public Tagger
{

public:

    HTopLeptonTagger();

    void SetTagger(const BottomTagger &NewBottomTagger);

    std::vector<HTopLeptonBranch> GetBranches(Event &event, const Object::Tag tag);

    std::vector<Doublet> GetBdt(const Jets &jets, const Jets &Leptons, const Reader &Reader);

    HTopLeptonBranch GetBranch(const Doublet &doublet) const;

    BottomTagger bottom_tagger_;

    Reader BottomReader;
protected:

    virtual  std::string ClassName() const {
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
    int eventNumber = 0;

};

}

}
