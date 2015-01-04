# ifndef HOctet44_hh
# define HOctet44_hh

# include "HQuartet31.hh"

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HOctet44 : public hanalysis::HTag
{

public:

    HOctet44(const hanalysis::HQuartet31& NewQuartet1, const hanalysis::HQuartet31& NewDoublet);

    hanalysis::HQuartet31 GetQuartet1()const {
        return Quartet1;
    }

    hanalysis::HQuartet31 GetQuartet2() const {
        return Quartet2;
    }

    fastjet::PseudoJet GetQuartet1Jet() const {
        return Quartet1.GetQuartetJet();
    }

    fastjet::PseudoJet GetQuartet2Jet() const {
        return Quartet2.GetQuartetJet();
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
        return "HOctet44";
    }

private:

    float GetDeltaR1() const {
        return GetQuartet1Jet().delta_R(GetQuartet2Jet());
    }

    float GetDeltaR2() const {
      return GetQuartet1Jet().delta_R(Quartet2.GetJet2());
    }

    float GetDeltaPhi1() const {
      return GetQuartet1Jet().delta_phi_to(Quartet2.GetJet1());
    }

    float GetDeltaPhi2() const {
      return GetQuartet1Jet().delta_phi_to(Quartet2.GetJet2());
    }

    float GetDeltaRap1() const {
      return (GetQuartet1Jet().rap() - Quartet2.GetJet1().rap());
    }

    float GetDeltaRap2() const {
        return (GetQuartet1Jet().rap() - Quartet2.GetJet2().rap());
    }

    hanalysis::HQuartet31 Quartet1;

    hanalysis::HQuartet31 Quartet2;

    int LeptonNumber;

    int BottomNumber;

    int JetNumber;

    int ScalarHt;

};

#endif
