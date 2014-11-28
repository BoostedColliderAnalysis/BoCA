# ifndef HLeptonicTopTagger_hh
# define HLeptonicTopTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HJetLeptonPair.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hdelphes::HLeptonicTopTagger : public hmva::HMva
{
    
public:
    
    HLeptonicTopTagger(HBottomTagger *NewBottomTagger);
    
    ~HLeptonicTopTagger();
    
    std::vector<HLeptonicTopBranch*> GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    
    void FillBranch(const hanalysis::HJetLeptonPair &JetLeptonPair);
    
private:
    
    HBottomTagger *BottomTagger;
    
    hmva::HReader *BottomReader;
    
    HLeptonicTopBranch *Branch;
    
    hanalysis::HJetTag *JetTag;
    
    void DefineVariables();
    
    void FillBranch(HLeptonicTopBranch *LeptonicTopBranch, const hanalysis::HJetLeptonPair &JetLeptonPair);

    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HLeptonicTopTagger";
    };

};

#endif
