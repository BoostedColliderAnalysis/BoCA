# ifndef HBottomTagger_hh
# define HBottomTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"

/**
 * @brief Bdt bottom tagger
 *
 */
class hanalysis::HBottomTagger : public HMva
{

public:

    HBottomTagger();

    ~HBottomTagger();

    std::vector< HBottomBranch * > GetBranches(HEvent *const Event, const hanalysis::HObject::HState State);

    void FillBranch(const fastjet::PseudoJet &Jet);

    HJets GetBottomBdt(HJets& Jets, const hanalysis::HReader*const BottomReader);

private:

    HBottomBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet);

    hanalysis::HObject::HState GetSingletTag(const fastjet::PseudoJet &Jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

};

#endif
