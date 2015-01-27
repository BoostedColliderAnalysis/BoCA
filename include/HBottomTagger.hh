# ifndef HBottomTagger_hh
# define HBottomTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HEvent.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
class hanalysis::HBottomTagger : public HMva
{

public:

    HBottomTagger();

    ~HBottomTagger();

    void SetTagger();

    std::vector< HBottomBranch > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    HJets GetBdt(HJets &Jets, const hanalysis::HReader &BottomReader);

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Jet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

private:

    void DefineVariables();

    HJets CleanJets(const HJets &Jets, const HTag Tag);

    HJets GetSubJets(const HJets &Jets, const HTag Tag, const int SubJetNumber);

    HJets GetSubBdt(HJets &Jets, const hanalysis::HReader &BottomReader, const int SubJetNumber);

    HJets GetJetBdt(HJets &Jets, const hanalysis::HReader &BottomReader);

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HBottomBranch Branch;
    HJetTag JetTag;

};

#endif
