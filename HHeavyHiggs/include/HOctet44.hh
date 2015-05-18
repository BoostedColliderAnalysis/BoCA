# ifndef HOctet44_hh
# define HOctet44_hh

# include "HQuartet31.hh"

struct HChargedevent_struct {

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
 * @brief An octet composed of two quartets
 *
 */
class HOctet44 : public analysis::Identification
{

public:

  HOctet44(){};

    HOctet44(const analysis::HQuartet31 &NewQuartet1, const analysis::HQuartet31 &Newdoublet);

    HOctet44(const analysis::HQuartet31 &NewQuartet1, const analysis::HQuartet31 &NewQuartet2, const HChargedevent_struct &Newevent_struct);

    inline analysis::HQuartet31 Quartet1()const {
        return Quartet1M;
    }

    inline analysis::HQuartet31 Quartet2() const {
        return Quartet2M;
    }
    inline fastjet::PseudoJet GetQuartet1Jet() const {
        return Quartet1M.Jet();
    }

    inline fastjet::PseudoJet GetQuartet2Jet() const {
        return Quartet2M.Jet();
    }

    inline  fastjet::PseudoJet Jet() const {
        return GetQuartet1Jet() + GetQuartet2Jet();
    }

    inline float Ht() const {
      return Quartet1().Ht() + Quartet2().Ht();
    }

    inline float DeltaPt() const {
        return GetQuartet1Jet().pt() - GetQuartet2Jet().pt();
    }

    inline float DeltaHt() const {
      return Quartet1().Ht() - Quartet2().Ht();
    }

    inline float DeltaM() const {
      return GetQuartet1Jet().m() - GetQuartet2Jet().m();
    }

    inline float DeltaR() const {
        return GetQuartet1Jet().delta_R(GetQuartet2Jet());
    }

    inline float DeltaPhi() const {
        return GetQuartet1Jet().delta_phi_to(GetQuartet2Jet());
    }

    inline float DeltaRap() const {
        return GetQuartet1Jet().rap() - GetQuartet2Jet().rap();
    }

    inline float BottomBdt() const {
      return Quartet1().singlet().user_info<analysis::JetInfo>().Bdt() + Quartet1().triplet().singlet().user_info<analysis::JetInfo>().Bdt() + Quartet2().singlet().user_info<analysis::JetInfo>().Bdt() + Quartet2().triplet().singlet().user_info<analysis::JetInfo>().Bdt();
    }

    inline float PairBottomBdt() const {
      return Quartet2().singlet().user_info<analysis::JetInfo>().Bdt() + Quartet2().triplet().singlet().user_info<analysis::JetInfo>().Bdt();
    }

//     inline float GetDeltaPt1() const {
//         return (DeltaR() + GetDeltaR2());
//     }
//
//     inline float GetHbDeltaDeltaR() const {
//         return std::abs(DeltaR() - GetDeltaR2());
//     }
//
//     inline float GetHbSumDeltaRap() const {
//         return DeltaRap() + GetDeltaRap2();
//     }
//
//     inline float GetHbDeltaDeltaRap() const {
//         return std::abs(DeltaRap() - GetDeltaRap2());
//     }
//
//     inline float GetHbSumDeltaPhi() const {
//         return GetDeltaPhi1() + GetDeltaPhi2();
//     }
//
//     inline float GetHbDeltaDeltaPhi() const {
//         return GetDeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
//     }

    inline void SetScalarHt(const float NewScalarHt) {
        event_structM.ScalarHt = NewScalarHt;
    }

    inline void SetJetNumber(const int NewJetNumber) {
        event_structM.JetNumber = NewJetNumber;
    }

    inline void SetBottomNumber(const int NewBottomNumber) {
        event_structM.BottomNumber = NewBottomNumber;
    }

    inline void SetLeptonNumber(const int NewLeptonNumber) {
        event_structM.LeptonNumber = NewLeptonNumber;
    }

    inline float ScalarHt() const {
        return event_structM.ScalarHt;
    }

    inline int JetNumber()const {
        return event_structM.JetNumber;
    }

    inline int BottomNumber()const {
        return event_structM.BottomNumber;
    }

    inline int LeptonNumber()const {
        return event_structM.LeptonNumber;
    }

    inline HChargedevent_struct event_struct()const {
        return event_structM;
    }

    inline void Setevent_struct(const HChargedevent_struct &Newevent_struct) {
        event_structM = Newevent_struct;
    }


    HChargedevent_struct event_structM;

//     int LeptonNumber;
//
//     int BottomNumber;
//
//     int JetNumber;
//
//     int ScalarHt;

protected:

    virtual inline std::string ClassName() const {
        return "HOctet44";
    }

private:

    analysis::HQuartet31 Quartet1M;

    analysis::HQuartet31 Quartet2M;

};

#endif
