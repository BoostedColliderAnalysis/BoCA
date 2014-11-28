# ifndef HJetLeptonPair_hh
# define HJetLeptonPair_hh

# include "HPair.hh"
# include "HJetInfo.hh"

class hanalysis::HJetLeptonPair : public HPair
{

public:
    
    HJetLeptonPair(){}
    
    HJetLeptonPair(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &Lepton);
    
    ~HJetLeptonPair();
    
    void SetJet(const fastjet::PseudoJet Jet){
        Jet1 = Jet;
    }
    
    void SetLepton(const fastjet::PseudoJet Lepton){
        Jet2 = Lepton;
    }
    
    fastjet::PseudoJet GetJet() const {
        return Jet1;
    }
    
    fastjet::PseudoJet GetLepton() const {
        return Jet2;
    }

    inline float GetJetPt() const {
        return Jet1.pt();
    }
    
    inline float GetLeptonPt() const {
        return Jet2.pt();
    }
    
    float GetBdt() const {
        return Jet1.user_info<HJetInfo>().GetBdt();
    }
protected:

    virtual inline std::string ClassName() const {
        return "HJetLeptonPair";
    };

    virtual inline std::string NameSpaceName() const {
        return "hanalysis";
    };

private:

};

#endif
