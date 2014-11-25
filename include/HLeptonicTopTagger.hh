# ifndef HLeptonicTopTagger_hh
# define HLeptonicTopTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HSuperStructure.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hdelphes::HLeptonicTopTagger : public hmva::HMva
{
    
public:
    
    HLeptonicTopTagger();
    
    ~HLeptonicTopTagger();
    
    std::vector< HLeptonicTopBranch * > GetTopTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State, HBottomTagger *BottomTagger);
    
    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&){ HReaderStruct ReaderStruct; return ReaderStruct;};
    
    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *){};
    
    float GetBdt(TObject *Branch, TMVA::Reader *Reader);
    
    //     std::vector<HLeptonicTopBranch *> GetBottomTag(hanalysis::HEvent *const Event, const HState State);
    
   
//     template<typename TMva>
    void SetMva() {
        
        Print(HNotification,"Set Mva");
        
        Reader = new hmva::HReader(this);
        Reader->AddVariable();
        Reader->BookMVA();
        
    }
    
    float GetTopBdt(const hdelphes::HSuperStructure &Top);
    
private:
    
    hmva::HReader *Reader;
    
    HLeptonicTopBranch *LeptonicTopTagger;
    
    hanalysis::HJetTag *JetTag;
    
    void DefineVariables();
    
    void FillTopBranch(const hdelphes::HSuperStructure &Pair, HLeptonicTopBranch *TopTagger);
    
    float GetDeltaR(const fastjet::PseudoJet &Jet);
    

    virtual inline std::string NameSpaceName() const {
        return "HDelphes";
    };

    virtual inline std::string ClassName() const {
        return "HLeptonicTopTagger";
    };

};

#endif
