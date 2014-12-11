# ifndef HTopLeptonicTagger_hh
# define HTopLeptonicTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HTriplet.hh"

/**
 * @brief Bdt leptonic top tagger
 *
 */
class hanalysis::HTopLeptonicTagger : public HMva
{

public:

    HTopLeptonicTagger(HBottomTagger *const NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector<HTopLeptonicBranch*> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HTriplet &Triple);

    HJets GetNeutrinos(const fastjet::PseudoJet &Lepton, const fastjet::PseudoJet &Bottom, const fastjet::PseudoJet &MissingEt)const;


private:

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HTopLeptonicBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();
    void FillBranch(HTopLeptonicBranch*const LeptonicTopBranch, const hanalysis::HTriplet& Triplet);


    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HTopLeptonicTagger";
    };

};

#endif
