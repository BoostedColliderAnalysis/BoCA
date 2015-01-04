# ifndef HOctet44_hh
# define HOctet44_hh

# include "HQuartet31.hh"

/**
 * @brief An octet composed of two quartets
 *
 */
class HOctet44 : public hanalysis::HTag
{

public:

    HOctet44(const hanalysis::HQuartet31& NewQuartet1, const hanalysis::HQuartet31& NewDoublet);

    inline  fastjet::PseudoJet GetOctetJet() const{
      return (GetQuartet1Jet() + GetQuartet2Jet());
    }

    inline hanalysis::HQuartet31 GetQuartet1()const {
        return Quartet1;
    }

    inline hanalysis::HQuartet31 GetQuartet2() const {
        return Quartet2;
    }

    inline fastjet::PseudoJet GetQuartet1Jet() const {
        return Quartet1.GetQuartetJet();
    }

    inline fastjet::PseudoJet GetQuartet2Jet() const {
        return Quartet2.GetQuartetJet();
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

    inline  int GetLeptonNumber()const {
        return LeptonNumber;
    }

protected:

    virtual inline std::string ClassName() const {
        return "HOctet44";
    }

private:

// TODO the following is wrong

    inline float GetDeltaR1() const {
        return GetQuartet1Jet().delta_R(GetQuartet2Jet());
    }

    inline float GetDeltaR2() const {
      return GetQuartet1Jet().delta_R(GetQuartet2Jet());
    }

    inline float GetDeltaPhi1() const {
      return GetQuartet1Jet().delta_phi_to(GetQuartet2Jet());
    }

    inline float GetDeltaPhi2() const {
      return GetQuartet1Jet().delta_phi_to(GetQuartet2Jet());
    }

    inline float GetDeltaRap1() const {
      return (GetQuartet1Jet().rap() - GetQuartet2Jet().rap());
    }

    inline float GetDeltaRap2() const {
      return (GetQuartet1Jet().rap() - GetQuartet2Jet().rap());
    }

    hanalysis::HQuartet31 Quartet1;

    hanalysis::HQuartet31 Quartet2;

    int LeptonNumber;

    int BottomNumber;

    int JetNumber;

    int ScalarHt;

};

#endif
