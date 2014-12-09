#ifndef HHeavyHiggsEvent_hh
#define HHeavyHiggsEvent_hh

# include "HTag.hh"
# include "HTriplePair.hh"

class HHeavyHiggsEvent : public hanalysis::HTag
{

public:

  HHeavyHiggsEvent(const hanalysis::HTriplePair &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom);

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

#endif
