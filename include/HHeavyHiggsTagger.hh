# ifndef HHeavyHiggsTagger_hh
# define HHeavyHiggsTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HLeptonicTopTagger.hh"
# include "HJetLeptonPair.hh"
# include "HPairPair.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsTagger : public HMva
{

public:

    HHeavyHiggsTagger(HBottomTagger *const NewBottomTagger, HLeptonicTopTagger *const NewTopTagger);

    ~HHeavyHiggsTagger();

    std::vector<HHeavyHiggsBranch *> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HTriplePair& TriplePair);

private:

    HBottomTagger *BottomTagger;
    
    HLeptonicTopTagger *TopTagger;

    HReader  *BottomReader;

    HReader  *TopReader;

    HHeavyHiggsBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHeavyHiggsBranch* HeavyHiggsBranch, const hanalysis::HTriplePair& TriplePair);

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTagger";
    };

};

#endif
