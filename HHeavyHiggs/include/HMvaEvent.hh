# ifndef HMvaHiggsCpv_hh
# define HMvaHiggsCpv_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HLeptonicTopTagger.hh"
# include "HHeavyHiggsTagger.hh"



class HOctet : public hanalysis::HTag
{

public:

  HOctet(const hanalysis::HSextet &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom) {
    SextetM = NewHeavyHiggs;
    Jet1 = NewBottom;
    Jet2 = NewAntiBottom;
  }

  hanalysis::HSextet Sextet()const {
    return SextetM;
  }

  float Bdt() const {
    return (SextetM.Bdt() * Jet1.user_info<hanalysis::HJetInfo>().Bdt() * Jet1.user_info<hanalysis::HJetInfo>().Bdt());
  }

  float DeltaRap() const {
    return (Jet1.rap() - Jet2.rap());
  }

  float DeltaPhi() const {
    return Jet1.delta_phi_to(Jet2);
  }

  float DeltaR() const {
    return Jet1.delta_R(Jet2);
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

  float ScalarHt() const {
    return ScalarHt;
  }
  int JetNumber()const {
    return JetNumber;
  }
  int BottomNumber()const {
    return BottomNumber;
  }
  int LeptonNumber()const {
    return LeptonNumber;
  }

private:

  float GetDeltaR1() const {
    return SextetM.GetPairJet().delta_R(Bottom);
  }

  float GetDeltaR2() const {
    return SextetM.GetPairJet().delta_R(AntiBottom);
  }

  float GetDeltaPhi1() const {
    return SextetM.GetPairJet().delta_phi_to(Bottom);
  }

  float GetDeltaPhi2() const {
    return SextetM.GetPairJet().delta_phi_to(AntiBottom);
  }

  float GetDeltaRap1() const {
    return (SextetM.GetPairJet().rap() - Jet1.rap());
  }

  float GetDeltaRap2() const {
    return (SextetM.GetPairJet().rap() - Jet2.rap());
  }

  fastjet::PseudoJet Jet1;
  fastjet::PseudoJet Jet2;
  hanalysis::HSextet SextetM;
  int LeptonNumber;
  int BottomNumber;
  int JetNumber;
  float ScalarHt;

};



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
    HMvaEvent(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HTopSemiTagger *const NewTopTagger, hanalysis::HHeavyHiggsTagger *const NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HMvaEvent();

    std::vector<hheavyhiggs::HEventLeptonicBranch *> GetBranches(hanalysis::HEvent *const Event, const HObject::HState State);

    void FillBranch(const HOctet &HeavyHiggsEvent);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &) {};

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *, TMVA::Reader *) {
        return 0;
    };

protected:


private:

    std::vector<HOctet> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    void FillBranch(hheavyhiggs::HEventLeptonicBranch *EventBranch, const HOctet &HeavyHiggsEvent);

    void DefineVariables();


    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HTopSemiTagger *LeptonicTopTagger;
    hanalysis::HHeavyHiggsTagger *HeavyHiggsTagger;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *TopReader;
    hanalysis::HReader *HeavyHiggsReader;

    hheavyhiggs::HEventLeptonicBranch *Branch;

    hanalysis::HJetTag *JetTag;

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HMvaEvent";
    };


};

# endif
