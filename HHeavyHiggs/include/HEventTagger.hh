# ifndef HEventTagger_hh
# define HEventTagger_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HLeptonicTopTagger.hh"
# include "HHeavyHiggsLeptonicTagger.hh"
# include "HHeavyHiggsHadronicTagger.hh"

class HHeavyHiggsEvent : public hanalysis::HTag
{
    
public:
    
    HHeavyHiggsEvent(const hanalysis::HTriplePair &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom) {
        HeavyHiggs = NewHeavyHiggs;
        Bottom = NewBottom;
        AntiBottom = NewAntiBottom;
    }
    
    hanalysis::HTriplePair GetHeavyHiggs()const {
        return HeavyHiggs;
    }
    
    float GetBdt() const {
        return (HeavyHiggs.GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt());
    }
    
    float GetBottomSumPt() const {
        return (Bottom.pt() + AntiBottom.pt());
    }
    
    float GetBottomDeltaPt() const {
        return std::abs(Bottom.pt() - AntiBottom.pt());
    }
    
    float GetBottomDeltaRap() const {
        return (Bottom.rap() - AntiBottom.rap());
    }
    
    float BottomDeltaPhi() const {
        return Bottom.delta_phi_to(AntiBottom);
    }
    
    float GetBottomDeltaR() const {
        return Bottom.delta_R(AntiBottom);
    }
    
    float GetHbSumDeltaR() const {
        return (GetDeltaR1() + GetDeltaR2());
    }
    
    float GetHbDeltaDeltaR() const {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }
    
    float GetHbSumDeltaRap() const {
        return GetDeltaRap1() + GetDeltaRap2();
    }
    
    float GetHbDeltaDeltaRap() const {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }
    
    float GetHbSumDeltaPhi() const {
        return GetDeltaPhi1() + GetDeltaPhi2();
    }
    
    float GetHbDeltaDeltaPhi() const {
        return GetDeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }
    
    void SetScalarHt(const float NewScalarHt) {
        ScalarHt = NewScalarHt;
    }
    
    void SetJetNumber(const int NewJetNumber) {
        JetNumber = NewJetNumber;
    }
    void SetBottomNumber(const int NewBottomNumber) {
        BottomNumber = NewBottomNumber;
    }
    
    void SetLeptonNumber(const int NewLeptonNumber) {
        LeptonNumber = NewLeptonNumber;
    }
    
    float GetScalarHt() const {
        return ScalarHt;
    }
    int GetJetNumber()const {
        return JetNumber;
    }
    int GetBottomNumber()const {
        return BottomNumber;
    }
    int GetLeptonNumber()const {
        return LeptonNumber;
    }
    
private:
    
    float GetDeltaR1() const {
        return HeavyHiggs.GetPairJet().delta_R(Bottom);
    }
    
    float GetDeltaR2() const {
        return HeavyHiggs.GetPairJet().delta_R(AntiBottom);
    }
    
    float GetDeltaPhi1() const {
        return HeavyHiggs.GetPairJet().delta_phi_to(Bottom);
    }
    
    float GetDeltaPhi2() const {
        return HeavyHiggs.GetPairJet().delta_phi_to(AntiBottom);
    }
    
    float GetDeltaRap1() const {
        return (HeavyHiggs.GetPairJet().rap() - Bottom.rap());
    }
    
    float GetDeltaRap2() const {
        return (HeavyHiggs.GetPairJet().rap() - AntiBottom.rap());
    }
    
    fastjet::PseudoJet Bottom;
    fastjet::PseudoJet AntiBottom;
    hanalysis::HTriplePair HeavyHiggs;
    int LeptonNumber;
    int BottomNumber;
    int JetNumber;
    int ScalarHt;
    
};

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HEventTagger : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HLeptonicTopTagger *const NewTopTagger, hanalysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HEventTagger();

    std::vector<hheavyhiggs::HEventBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &) {};

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:
    
    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    void FillBranch(hheavyhiggs::HEventBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HLeptonicTopTagger *LeptonicTopTagger;
    hanalysis::HHeavyHiggsLeptonicTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *TopReader;
    hanalysis::HReader *HeavyHiggsReader;
    
    hheavyhiggs::HEventBranch *Branch;

    hanalysis::HJetTag *JetTag;
       
    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HEventTagger";
    };


};

# endif
