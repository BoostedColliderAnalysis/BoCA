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

    std::vector< HBottomBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    void FillBranch(const fastjet::PseudoJet &Jet);

    HJets CleanJets(const HJets &Jets, const HTag Tag);

    HJets GetSubJets(const HJets &Jets, const int SubJetNumber, const HTag Tag);


//     HJets GetTruthJets(hanalysis::HEvent*const Event, const hanalysis::HReader*const BottomReader);

//     HJets GetTruthBdt(HJets& Jets, const hanalysis::HReader*const BottomReader);

    HJets GetBdt(HJets& Jets, const hanalysis::HReader*const BottomReader);
    HJets GetBdt2(HJets& Jets, const hanalysis::HReader*const BottomReader);

    void FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet);
protected:

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

private:

  void DefineVariables();
  HJets GetSubBdt(HJets& Jets, const hanalysis::HReader*const BottomReader, const int SubJetNumber);

  HJets GetJetBdt(HJets& Jets, const hanalysis::HReader*const BottomReader);

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Jet) const;
//     hanalysis::HObject::HTag GetTag(const HJetInfo &JetInfo) const;

    HBottomBranch *Branch;

    HJetTag *JetTag;

};

#endif
