# ifndef HMvaHiggsCpv_hh
# define HMvaHiggsCpv_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HLeptonicTopTagger.hh"
# include "HHeavyHiggsTagger.hh"



class HHeavyHiggsEvent : public hanalysis::HTag
{

public:

  HHeavyHiggsEvent(const hanalysis::HSextet &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom) {
    HeavyHiggs = NewHeavyHiggs;
    Bottom = NewBottom;
    AntiBottom = NewAntiBottom;
  }

  hanalysis::HSextet GetHeavyHiggs()const {
    return HeavyHiggs;
  }

  float GetBdt() const {
    return (HeavyHiggs.GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt());
  }

  float GetDeltaRap() const {
    return (Bottom.rap() - AntiBottom.rap());
  }

  float DeltaPhi() const {
    return Bottom.delta_phi_to(AntiBottom);
  }

  float GetDeltaR() const {
    return Bottom.delta_R(AntiBottom);
  }

  float GetDeltaRSum() const {
    return GetDeltaR1() + GetDeltaR2();
  }

  float GetDeltaRDiff() const {
    return std::abs(GetDeltaR1() - GetDeltaR2());
  }

  float GetDeltaRapSum() const {
    return GetDeltaRap1() + GetDeltaRap2();
  }

  float GetDeltaRapDiff() const {
    return std::abs(GetDeltaRap1() - GetDeltaRap2());
  }

  float GetDeltaPhiSum() const {
    return GetDeltaPhi1() + GetDeltaPhi2();
  }

  float GetDeltaPhiDiff() const {
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
  hanalysis::HSextet HeavyHiggs;
  int LeptonNumber;
  int BottomNumber;
  int JetNumber;
  float ScalarHt;

};

# endif


/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HMvaEvent : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaEvent(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HLeptonicTopTagger *const NewTopTagger, hanalysis::HHeavyHiggsTagger *const NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HMvaEvent();

    std::vector<hheavyhiggs::HLeptonicEventBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HHeavyHiggsEvent &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &) {};

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    void FillBranch(hheavyhiggs::HLeptonicEventBranch *EventBranch, const HHeavyHiggsEvent &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HLeptonicTopTagger *LeptonicTopTagger;
    hanalysis::HHeavyHiggsTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *TopReader;
    hanalysis::HReader *HeavyHiggsReader;

    hheavyhiggs::HLeptonicEventBranch *Branch;

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HMvaEvent";
    };


};

# endif
