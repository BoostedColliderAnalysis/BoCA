# ifndef HHeavyHiggsMixedTagger_hh
# define HHeavyHiggsMixedTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HTopLeptonicTagger.hh"
# include "HHadronicTopTagger.hh"
# include "HJetLeptonPair.hh"
# include "HPairPair.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsMixedTagger : public HMva
{

public:

    HHeavyHiggsMixedTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopLeptonicTagger *const NewTopLeptonicTagger, hanalysis::HHadronicTopTagger *const NewTopHadronicTagger);

    ~HHeavyHiggsMixedTagger();

    std::vector<HHeavyHiggsMixedBranch *> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HTriplePair& TriplePair);

private:

    HTriplePair GetTriplePair(HJets &Jets, fastjet::PseudoJet Lepton,fastjet::PseudoJet MissingEt,const hanalysis::HObject::HState State);

    HBottomTagger *BottomTagger;
    HWTagger *WTagger;
    HHadronicTopTagger *TopHadronicTagger;
    HTopLeptonicTagger *TopLeptonicTagger;

    HReader *BottomReader;
    HReader *WReader;
    HReader *TopHadronicReader;
    HReader *TopLeptonicReader;

    HHeavyHiggsMixedBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHeavyHiggsMixedBranch* HeavyHiggsBranch, const hanalysis::HTriplePair& TriplePair);

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsMixedTagger";
    };

};

#endif
