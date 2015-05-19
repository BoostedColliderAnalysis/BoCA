# ifndef HOctet44_hh
# define HOctet44_hh

# include "Quartet31.hh"

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

    HOctet44(const analysis::Quartet31 &Newquartet1, const analysis::Quartet31 &Newdoublet);

    HOctet44(const analysis::Quartet31 &Newquartet1, const analysis::Quartet31 &Newquartet2, const HChargedevent_struct &Newevent_struct);

    inline analysis::Quartet31 quartet1()const {
        return quartet1M;
    }

    inline analysis::Quartet31 quartet2() const {
        return quartet2M;
    }
    inline fastjet::PseudoJet Getquartet1Jet() const {
        return quartet1M.Jet();
    }

    inline fastjet::PseudoJet Getquartet2Jet() const {
        return quartet2M.Jet();
    }

    inline  fastjet::PseudoJet Jet() const {
        return Getquartet1Jet() + Getquartet2Jet();
    }

    inline float Ht() const {
      return quartet1().Ht() + quartet2().Ht();
    }

    inline float DeltaPt() const {
        return Getquartet1Jet().pt() - Getquartet2Jet().pt();
    }

    inline float DeltaHt() const {
      return quartet1().Ht() - quartet2().Ht();
    }

    inline float DeltaM() const {
      return Getquartet1Jet().m() - Getquartet2Jet().m();
    }

    inline float DeltaR() const {
        return Getquartet1Jet().delta_R(Getquartet2Jet());
    }

    inline float DeltaPhi() const {
        return Getquartet1Jet().delta_phi_to(Getquartet2Jet());
    }

    inline float DeltaRap() const {
        return Getquartet1Jet().rap() - Getquartet2Jet().rap();
    }

    inline float BottomBdt() const {
      return quartet1().singlet().user_info<analysis::JetInfo>().Bdt() + quartet1().triplet().singlet().user_info<analysis::JetInfo>().Bdt() + quartet2().singlet().user_info<analysis::JetInfo>().Bdt() + quartet2().triplet().singlet().user_info<analysis::JetInfo>().Bdt();
    }

    inline float PairBottomBdt() const {
      return quartet2().singlet().user_info<analysis::JetInfo>().Bdt() + quartet2().triplet().singlet().user_info<analysis::JetInfo>().Bdt();
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

    analysis::Quartet31 quartet1M;

    analysis::Quartet31 quartet2M;

};

#endif
