# ifndef HTopLeptonicTagger_hh
# define HTopLeptonicTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief Bdt top semi leptonic tagger
 *
 */
class hanalysis::HTopLeptonicTagger : public HMva
{

public:

    HTopLeptonicTagger(HBottomTagger *const NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector<HTopLeptonicBranch*> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const HDoublet &Doublet);

private:

    HBottomTagger *BottomTagger;
    HReader *BottomReader;
    HTopLeptonicBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    HState GetDoubletTag(const HDoublet &Doublet);

    void FillBranch(HTopLeptonicBranch *const TopLeptonicBranch, const HDoublet &Doublet);

    virtual inline std::string ClassName() const {
        return "HTopLeptonicTagger";
    };

};

#endif
