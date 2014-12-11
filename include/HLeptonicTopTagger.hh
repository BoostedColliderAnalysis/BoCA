# ifndef HLeptonicTopTagger_hh
# define HLeptonicTopTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief Bdt leptonic top tagger
 *
 */
class hanalysis::HLeptonicTopTagger : public HMva
{

public:

    HLeptonicTopTagger(HBottomTagger *const NewBottomTagger);

    ~HLeptonicTopTagger();

    std::vector<HLeptonicTopBranch*> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const HDoublet &JetLeptonPair);

private:

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HLeptonicTopBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HLeptonicTopBranch *const LeptonicTopBranch, const HDoublet &JetLeptonPair);

    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HLeptonicTopTagger";
    };

};

#endif
