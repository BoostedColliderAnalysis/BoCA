# ifndef HHeavyHiggsLeptonicTagger_hh
# define HHeavyHiggsLeptonicTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HDoublet.hh"
# include "HQuartet.hh"
# include "HTopLeptonicTagger.hh"

/**
 * @brief Bdt heavy higgs tagger
 *
 */
class hanalysis::HHeavyHiggsLeptonicTagger : public HMva
{

public:

    HHeavyHiggsLeptonicTagger(hanalysis::HBottomTagger*const NewBottomTagger, hanalysis::HTopLeptonicTagger*const NewTopLeptonicTagger);

    ~HHeavyHiggsLeptonicTagger();

    std::vector<HHeavyHiggsLeptonicBranch *> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HSextet& TriplePair);

private:

    HBottomTagger *BottomTagger;
    HTopLeptonicTagger *TopLeptonicTagger;

    HReader *BottomReader;
    HReader *TopLeptonicReader;

    HHeavyHiggsLeptonicBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    hanalysis::HObject::HState GetQuartetTag(const HQuartet &Quartet);

    void FillBranch(HHeavyHiggsLeptonicBranch* HeavyHiggsBranch, const hanalysis::HSextet& TriplePair);

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsLeptonicTagger";
    };

};

#endif
