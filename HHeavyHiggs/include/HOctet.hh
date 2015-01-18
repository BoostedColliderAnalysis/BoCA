# ifndef HOctet_hh
# define HOctet_hh

# include "HDoublet.hh"
# include "HSextet.hh"


struct HEventStruct {

  int LeptonNumber = 0;
  int JetNumber = 0;
  int BottomNumber = 0;
  float ScalarHt = 0;
  float RestHt = 0;
  float RestM = 0;
  float RestPt = 0;
  float RestRap = 0;
  float RestPhi = 0;
  int RestBTag = 0;
  float RestBBdt = 0;
  float MaxBBdt = 0;
  float TotalBBdt = 0;
  float ThirdBBdt = 0;
  float LeptonPt = 0;

};

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HOctet : public hanalysis::HTag
{

public:

  HOctet(){};

  HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &Doublet);

  HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &Doublet, const HEventStruct &NewEventStruct);


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

  inline fastjet::PseudoJet GetOctetJet() const {
    return (GetSextetJet() + GetDoubletJet());
  }

  inline float GetDeltaPt() const {
    return GetSextetJet().pt() - GetDoubletJet().pt();
  }

  inline float GetDeltaR() const {
    return GetSextetJet().delta_R(GetDoubletJet());
  }

  inline float GetDeltaRap() const {
    return std::abs(GetSextetJet().rap() + GetDoubletJet().rap());
  }

  inline float GetDeltaPhi() const {
    return GetSextetJet().delta_phi_to(GetDoubletJet());
  }

  inline float GetHbDeltaDeltaR() const {
    return std::abs(GetDeltaR1() - GetDeltaR2());
  }

  inline float GetHbDeltaDeltaRap() const {
    return std::abs(GetDeltaRap1() - GetDeltaRap2());
  }

  inline float GetHbDeltaDeltaPhi() const {
    return HObject::GetDeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
  }

  inline void SetScalarHt(const float NewScalarHt) {
    EventStruct.ScalarHt = NewScalarHt;
  }

  inline void SetJetNumber(const int NewJetNumber) {
    EventStruct.JetNumber = NewJetNumber;
  }

  inline void SetBottomNumber(const int NewBottomNumber) {
    EventStruct.BottomNumber = NewBottomNumber;
  }

  inline void SetLeptonNumber(const int NewLeptonNumber) {
    EventStruct.LeptonNumber = NewLeptonNumber;
  }

  inline float GetScalarHt() const {
    return EventStruct.ScalarHt;
  }

  inline int GetJetNumber()const {
    return EventStruct.JetNumber;
  }

  inline int GetBottomNumber()const {
    return EventStruct.BottomNumber;
  }

  inline int GetLeptonNumber()const {
    return EventStruct.LeptonNumber;
  }

  inline HEventStruct GetEventStruct()const {
    return EventStruct;
  }

  inline void SetEventStruct(const HEventStruct &NewEventStruct){
    EventStruct = NewEventStruct;
  }

  HEventStruct EventStruct;

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

  inline float GetDeltaPt1() const {
    return (GetSextetJet().pt() - Doublet.GetJet1().pt());
  }

  inline float GetDeltaPt2() const {
    return (GetSextetJet().pt() - Doublet.GetJet2().pt());
  }


protected:

  virtual inline std::string ClassName() const {
    return "HOctet";
  }

private:

  hanalysis::HSextet Sextet;

  hanalysis::HDoublet Doublet;

};

#endif
