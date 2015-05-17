# ifndef HOctet_hh
# define HOctet_hh

# include "Doublet.hh"
# include "HSextet.hh"


// struct EventStruct {
//
//     int LeptonNumber = 0;
//     int JetNumber = 0;
//     int BottomNumber = 0;
//     float ScalarHt = 0;
//     float RestHt = 0;
//     float RestM = 0;
//     float RestPt = 0;
//     float RestRap = 0;
//     float RestPhi = 0;
//     int RestBTag = 0;
//     float RestBBdt = 0;
//     float MaxBBdt = 0;
//     float TotalBBdt = 0;
//     float ThirdBBdt = 0;
//     float LeptonPt = 0;
//
// };

class HOctetPrivate;

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HOctet : public analysis::HTag
{

public:

    HOctet() {};

    HOctet(const analysis::HSextet &NewSextet, const analysis::Doublet &Newdoublet);

//     HOctet(const analysis::HSextet &NewSextet, const analysis::Doublet &Newdoublet, const EventStruct &NeweventStruct);


    inline analysis::HSextet Sextet()const {
        return SextetM;
    }

    inline analysis::Doublet doublet() const {
        return doubletM;
    }

    inline fastjet::PseudoJet SextetJet() const {
        return SextetM.Jet();
    }

    inline fastjet::PseudoJet doublet_jet() const {
        return doubletM.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return SextetJet() + doublet_jet();
    }

    inline float Ht() const {
        return SextetM.Ht() + doubletM.Ht();
    }

    inline float DeltaPt() const {
        return SextetJet().pt() - doublet_jet().pt();
    }

    inline float DeltaHt() const {
        return Sextet().Ht() - doublet().Ht();
    }

    inline float DeltaM() const {
        return SextetJet().m() - doublet_jet().m();
    }

    inline float DeltaR() const {
        return SextetJet().delta_R(doublet_jet());
    }

    inline float DeltaRap() const {
        return SextetJet().rap() - doublet_jet().rap();
    }

    inline float DeltaPhi() const {
        return SextetJet().delta_phi_to(doublet_jet());
    }

    inline float HbDeltaDeltaR() const {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }

    inline float HbDeltaDeltaRap() const {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }

    inline float HbDeltaDeltaPhi() const {
        return Object::GetDeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }

    inline float BottomBdt() const {
        return doublet().Singlet1().user_info<analysis::JetInfo>().Bdt() + doublet().Singlet2().user_info<analysis::JetInfo>().Bdt() + Sextet().triplet1().singlet().user_info<analysis::JetInfo>().Bdt() + Sextet().triplet2().singlet().user_info<analysis::JetInfo>().Bdt();
    }

    inline float PairBottomBdt() const {
        return doublet().Singlet1().user_info<analysis::JetInfo>().Bdt() + doublet().Singlet2().user_info<analysis::JetInfo>().Bdt();
    }
//
//     inline void SetJetNumber(const int NewJetNumber) {
//         eventStructM.JetNumber = NewJetNumber;
//     }
//
//     inline void SetBottomNumber(const int NewBottomNumber) {
//         eventStructM.BottomNumber = NewBottomNumber;
//     }
//
//     inline void SetLeptonNumber(const int NewLeptonNumber) {
//         eventStructM.LeptonNumber = NewLeptonNumber;
//     }
//
//     inline float ScalarHt() const {
//         return eventStructM.ScalarHt;
//     }
//
//     inline int JetNumber()const {
//         return eventStructM.JetNumber;
//     }
//
//     inline int BottomNumber()const {
//         return eventStructM.BottomNumber;
//     }
//
//     inline int LeptonNumber()const {
//         return eventStructM.LeptonNumber;
//     }
//
//     inline EventStruct eventStruct()const {
//         return eventStructM;
//     }
//
//     inline void SeteventStruct(const EventStruct &NeweventStruct) {
//         eventStructM = NeweventStruct;
//     }

//     EventStruct eventStructM;

    inline float GetDeltaR1() const {
        return SextetJet().delta_R(doubletM.Singlet1());
    }

    inline float GetDeltaR2() const {
        return SextetJet().delta_R(doubletM.Singlet2());
    }

    inline float GetDeltaPhi1() const {
        return SextetJet().delta_phi_to(doubletM.Singlet1());
    }

    inline float GetDeltaPhi2() const {
        return SextetJet().delta_phi_to(doubletM.Singlet2());
    }

    inline float GetDeltaRap1() const {
        return (SextetJet().rap() - doubletM.Singlet1().rap());
    }

    inline float GetDeltaRap2() const {
        return (SextetJet().rap() - doubletM.Singlet2().rap());
    }

    inline float GetDeltaPt1() const {
        return (SextetJet().pt() - doubletM.Singlet1().pt());
    }

    inline float GetDeltaPt2() const {
        return (SextetJet().pt() - doubletM.Singlet2().pt());
    }


protected:

    virtual inline std::string ClassName() const {
        return "HOctet";
    }

private:

    analysis::HSextet SextetM;

    analysis::Doublet doubletM;

};

#endif
