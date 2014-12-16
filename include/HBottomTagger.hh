# ifndef HBottomTagger_hh
# define HBottomTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
class hanalysis::HBottomTagger : public HMva
{

public:

    HBottomTagger();

    ~HBottomTagger();

    std::vector< HBottomBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const fastjet::PseudoJet &Jet);

    HJets GetTruthBdt(HJets& Jets, const hanalysis::HReader*const BottomReader);
    HJets GetBdt(HJets& Jets, const hanalysis::HReader*const BottomReader);

protected:

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

private:

    void DefineVariables();

    void FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet);

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Jet) const;

    HBottomBranch *Branch;

    HJetTag *JetTag;

};

#endif
