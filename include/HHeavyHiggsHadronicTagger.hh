# ifndef HHeavyHiggsHadronicTagger_hh
# define HHeavyHiggsHadronicTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HHadronicTopTagger.hh"
# include "HJetLeptonPair.hh"
# include "HPairPair.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsHadronicTagger : public HMva
{

public:

    HHeavyHiggsHadronicTagger(HBottomTagger *const NewBottomTagger,HWTagger *const NewWTagger, HHadronicTopTagger *const NewTopTagger);

    ~HHeavyHiggsHadronicTagger();

    std::vector<HHeavyHiggsHadronicBranch *> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HTriplePair& TriplePair);

private:

    std::vector< hanalysis::HTriplePair > GetTriplePairs(const HJets &Jets, const hanalysis::HObject::HState State);

    HBottomTagger *BottomTagger;
    HWTagger *WTagger;
    HHadronicTopTagger *TopHadronicTagger;

    HReader *BottomReader;
    HReader *WReader;
    HReader *TopHadronicReader;

    HHeavyHiggsHadronicBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHeavyHiggsHadronicBranch* HeavyHiggsBranch, const hanalysis::HTriplePair& TriplePair);

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsHadronicTagger";
    };

};

#endif
