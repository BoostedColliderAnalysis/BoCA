#ifndef HOctet_hh
#define HOctet_hh

# include "HSextet.hh"

class HOctet : public hanalysis::HTag
{

public:

  HOctet(const hanalysis::HSextet &NewSextet, const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2);

  hanalysis::HSextet GetSextet()const {
    return Sextet;
  }

  fastjet::PseudoJet GetJet1() const {
    return Jet1;
  }

  fastjet::PseudoJet GetJet2() const {
    return Jet2;
  }

  fastjet::PseudoJet GetSextetJet() const {
    return Sextet.GetSextetJet();
  }

  fastjet::PseudoJet GetJetsJet() const {
    return Jet1 + Jet2;
  }

//   float GetBdt() const {
//     return (Sextet.GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt());
//   }

//   float GetBottomSumPt() const {
//     return (Jet1.pt() + Jet2.pt());
//   }

  float GetBottomDeltaPt() const {
    return std::abs(Jet1.pt() - Jet2.pt());
  }

  float GetBottomDeltaRap() const {
    return (Jet1.rap() - Jet2.rap());
  }

  float BottomDeltaPhi() const {
    return Jet1.delta_phi_to(Jet2);
  }

  float GetBottomDeltaR() const {
    return Jet1.delta_R(Jet2);
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
    return GetSextetJet().delta_R(Jet1);
  }

  float GetDeltaR2() const {
    return GetSextetJet().delta_R(Jet2);
  }

  float GetDeltaPhi1() const {
    return GetSextetJet().delta_phi_to(Jet1);
  }

  float GetDeltaPhi2() const {
    return GetSextetJet().delta_phi_to(Jet2);
  }

  float GetDeltaRap1() const {
    return (GetSextetJet().rap() - Jet1.rap());
  }

  float GetDeltaRap2() const {
    return (GetSextetJet().rap() - Jet2.rap());
  }

  fastjet::PseudoJet Jet1;
  fastjet::PseudoJet Jet2;
  hanalysis::HSextet Sextet;
  int LeptonNumber;
  int BottomNumber;
  int JetNumber;
  int ScalarHt;

};

#endif
