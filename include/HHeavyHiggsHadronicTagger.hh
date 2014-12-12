# ifndef HHeavyHiggsHadronicTagger_hh
# define HHeavyHiggsHadronicTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HDoublet.hh"
# include "HQuartet.hh"
# include "HTopHadronicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsHadronicTagger : public HMva
{

public:

    HHeavyHiggsHadronicTagger(HBottomTagger *const NewBottomTagger,HWTagger *const NewWTagger, HTopHadronicTagger *const NewTopTagger);

    ~HHeavyHiggsHadronicTagger();

    std::vector<HHeavyHiggsHadronicBranch *> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HSextet& TriplePair);

private:

    HState GetTripletTag(const hanalysis::HTriplet& Triplet);

    HState GetDoubletTag(const HDoublet &Doublet);

    HState GetSextetTag(const HSextet &Sextet);

    HSextet GetTriplePair(HJets &Jets, const hanalysis::HObject::HState State);

    HBottomTagger *BottomTagger;
    HWTagger *WTagger;
    HTopHadronicTagger *TopHadronicTagger;

    HReader *BottomReader;
    HReader *WReader;
    HReader *TopHadronicReader;

    HHeavyHiggsHadronicBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHeavyHiggsHadronicBranch* HeavyHiggsBranch, const hanalysis::HSextet& TriplePair);

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsHadronicTagger";
    };

};

#endif
