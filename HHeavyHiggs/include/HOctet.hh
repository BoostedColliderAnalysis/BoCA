# ifndef HOctet_hh
# define HOctet_hh

# include "HDoublet.hh"
# include "HSextet.hh"

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HOctet : public hanalysis::HTag
{

public:

  HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &Doublet);

  hanalysis::HSextet GetSextet()const {
    return Sextet;
  }

  hanalysis::HDoublet GetDoublet() const{
    return Doublet;
  }

  fastjet::PseudoJet GetSextetJet() const {
    return Sextet.GetSextetJet();
  }

  fastjet::PseudoJet GetDoubletJet() const {
    return Doublet.GetDoubletJet();
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

protected:

  virtual inline std::string ClassName() const {
    return "HOctet";
  }

private:

  float GetDeltaR1() const {
    return GetSextetJet().delta_R(Doublet.GetJet1());
  }

  float GetDeltaR2() const {
    return GetSextetJet().delta_R(Doublet.GetJet2());
  }

  float GetDeltaPhi1() const {
    return GetSextetJet().delta_phi_to(Doublet.GetJet1());
  }

  float GetDeltaPhi2() const {
    return GetSextetJet().delta_phi_to(Doublet.GetJet2());
  }

  float GetDeltaRap1() const {
    return (GetSextetJet().rap() - Doublet.GetJet1().rap());
  }

  float GetDeltaRap2() const {
    return (GetSextetJet().rap() - Doublet.GetJet2().rap());
  }

  hanalysis::HSextet Sextet;

  hanalysis::HDoublet Doublet;

  int LeptonNumber;

  int BottomNumber;

  int JetNumber;

  int ScalarHt;

};

#endif
