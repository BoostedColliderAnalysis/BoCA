# ifndef HHeavyHiggsLeptonicTagger_hh
# define HHeavyHiggsLeptonicTagger_hh

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
class hanalysis::HHeavyHiggsLeptonicTagger : public HMva
{

public:

    HHeavyHiggsLeptonicTagger(HBottomTagger *const NewBottomTagger, HLeptonicTopTagger *const NewTopTagger);

    ~HHeavyHiggsLeptonicTagger();

    std::vector<HHeavyHiggsLeptonicBranch *> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HTriplePair& TriplePair);

private:

    HBottomTagger *BottomTagger;    
    HLeptonicTopTagger *TopTagger;

    HReader *BottomReader;
    HReader *TopReader;

    HHeavyHiggsLeptonicBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHeavyHiggsLeptonicBranch* HeavyHiggsBranch, const hanalysis::HTriplePair& TriplePair);

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsLeptonicTagger";
    };

};

#endif
