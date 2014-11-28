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
    
    std::vector< HBottomBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
        
//     float GetBdt(const fastjet::PseudoJet &Bottom, TMVA::Reader *Reader);
    
    HBottomBranch *Branch;
    void FillBranch(const fastjet::PseudoJet &Jet);    
    
private:
        
    hanalysis::HJetTag *JetTag;
    
    void DefineVariables();
    
    void FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet);

    
    float GetDeltaR(const fastjet::PseudoJet &Jet) const;
    

    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

};

#endif
