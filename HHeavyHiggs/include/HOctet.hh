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

  inline hanalysis::HSextet GetSextet()const {
    return Sextet;
  }

  inline hanalysis::HDoublet GetDoublet() const{
    return Doublet;
  }

  inline fastjet::PseudoJet GetSextetJet() const {
    return Sextet.GetSextetJet();
  }

  inline fastjet::PseudoJet GetDoubletJet() const {
    return Doublet.GetDoubletJet();
  }

  inline float GetHbSumDeltaR() const {
    return (GetDeltaR1() + GetDeltaR2());
  }

  inline float GetHbDeltaDeltaR() const {
    return std::abs(GetDeltaR1() - GetDeltaR2());
  }

  inline float GetHbSumDeltaRap() const {
    return GetDeltaRap1() + GetDeltaRap2();
  }

  inline float GetHbDeltaDeltaRap() const {
    return std::abs(GetDeltaRap1() - GetDeltaRap2());
  }

  inline float GetHbSumDeltaPhi() const {
    return GetDeltaPhi1() + GetDeltaPhi2();
  }

  inline float GetHbDeltaDeltaPhi() const {
    return GetDeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
  }

  inline void SetScalarHt(const float NewScalarHt) {
    ScalarHt = NewScalarHt;
  }

  inline void SetJetNumber(const int NewJetNumber) {
    JetNumber = NewJetNumber;
  }

  inline void SetBottomNumber(const int NewBottomNumber) {
    BottomNumber = NewBottomNumber;
  }

  inline void SetLeptonNumber(const int NewLeptonNumber) {
    LeptonNumber = NewLeptonNumber;
  }

  inline float GetScalarHt() const {
    return ScalarHt;
  }

  inline int GetJetNumber()const {
    return JetNumber;
  }

  inline int GetBottomNumber()const {
    return BottomNumber;
  }

  inline int GetLeptonNumber()const {
    return LeptonNumber;
  }

protected:

  virtual inline std::string ClassName() const {
    return "HOctet";
  }

private:

  inline float GetDeltaR1() const {
    return GetSextetJet().delta_R(Doublet.GetJet1());
  }

  inline float GetDeltaR2() const {
    return GetSextetJet().delta_R(Doublet.GetJet2());
  }

  inline float GetDeltaPhi1() const {
    return GetSextetJet().delta_phi_to(Doublet.GetJet1());
  }

  inline float GetDeltaPhi2() const {
    return GetSextetJet().delta_phi_to(Doublet.GetJet2());
  }

  inline float GetDeltaRap1() const {
    return (GetSextetJet().rap() - Doublet.GetJet1().rap());
  }

  inline float GetDeltaRap2() const {
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
