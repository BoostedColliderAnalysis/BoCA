# ifndef HHadronicWTagger_hh
# define HHadronicWTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief Bdt W tagger
 *
 */
class hanalysis::HWTagger : public HMva
{

public:

    HWTagger(HBottomTagger *NewBottomTagger);

    ~HWTagger();

    std::vector< HWBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    std::vector<HParticleBranch *> GetConstituentBranches();

    void FillBranch(const HDoublet &Pair);
    std::vector<HDoublet> GetWBdt(HJets& Jets, const hanalysis::HReader*const WReader, const hanalysis::HObject::HState State);

private:

    HBottomTagger *BottomTagger;
    HReader *BottomReader;
    HWBranch *Branch;
    HJetTag *JetTag;

    hanalysis::HObject::HState GetDoubletTag(const HDoublet &Doublet);



    void DefineVariables();

    void FillBranch(HWBranch *const WBranch, const hanalysis::HDoublet &Doublet);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    };

};

#endif
