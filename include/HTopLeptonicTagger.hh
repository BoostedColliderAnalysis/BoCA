# ifndef HTopLeptonicTagger_hh
# define HTopLeptonicTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HTriple.hh"

/**
 * @brief Bdt leptonic top tagger
 *
 */
class hanalysis::HTopLeptonicTagger : public HMva
{

public:

    HTopLeptonicTagger(HBottomTagger *const NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector<HLeptonicTopBranch*> GetBranches(HEvent *const Event, const HObject::HState State);

    void FillBranch(const hanalysis::HTriple &JetLeptonPair);

private:

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HLeptonicTopBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();
    
    HJets GetNeutrinos(const fastjet::PseudoJet &Lepton, const fastjet::PseudoJet &Bottom, const fastjet::PseudoJet &MissingEt)const;

    void FillBranch(HLeptonicTopBranch *const LeptonicTopBranch, const hanalysis::HTriple &JetLeptonPair);
   
    
    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HTopLeptonicTagger";
    };

};

#endif
