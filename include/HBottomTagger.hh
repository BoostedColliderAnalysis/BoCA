# ifndef HBottomTagger_hh
# define HBottomTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hdelphes::HBottomTagger : public hmva::HMva
{
    
public:
    
    HBottomTagger();
    
    ~HBottomTagger();
    
    std::vector< HBottomBranch * > GetBottomTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    
    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&){ HReaderStruct ReaderStruct; return ReaderStruct;};
    
    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *){};
    
    float GetBdt(TObject *Branch, TMVA::Reader *Reader);
    
//     std::vector<HBottomBranch *> GetBottomTag(hanalysis::HEvent *const Event, const HState State);
    
   
//     template<typename TMva>
    void SetMva() {
        
        Print(HNotification,"Set Mva");
        
        Reader = new hmva::HReader(this);
        Reader->AddVariable();
        Reader->BookMVA();
        
    }
    
    float GetBottomBdt(const fastjet::PseudoJet &Bottom);
    
private:
    
    hmva::HReader *Reader;
    
    HBottomBranch *BTagger;
    
    hanalysis::HJetTag *JetTag;
    
    void DefineVariables();
    
    void FillBottomBranch(const fastjet::PseudoJet &Jet, HBottomBranch *BTagger);
    
    float GetDeltaR(const fastjet::PseudoJet &Jet);
    

    virtual inline std::string NameSpaceName() const {
        return "HDelphes";
    };

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

};

#endif
