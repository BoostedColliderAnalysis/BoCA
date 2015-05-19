# ifndef HOctet_hh
# define HOctet_hh

# include "Doublet.hh"
# include "Sextet.hh"


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
class HOctet : public analysis::Identification
{

public:

    HOctet() {};

    HOctet(const analysis::Sextet &Newsextet, const analysis::Doublet &Newdoublet);

//     HOctet(const analysis::Hsextet &Newsextet, const analysis::Doublet &Newdoublet, const EventStruct &Newevent_struct);


    inline analysis::Sextet sextet()const {
        return sextetM;
    }

    inline analysis::Doublet doublet() const {
        return doubletM;
    }

    inline fastjet::PseudoJet sextetJet() const {
        return sextetM.Jet();
    }

    inline fastjet::PseudoJet doublet_jet() const {
        return doubletM.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return sextetJet() + doublet_jet();
    }

    inline float Ht() const {
        return sextetM.Ht() + doubletM.Ht();
    }

    inline float DeltaPt() const {
        return sextetJet().pt() - doublet_jet().pt();
    }

    inline float DeltaHt() const {
        return sextet().Ht() - doublet().Ht();
    }

    inline float DeltaM() const {
        return sextetJet().m() - doublet_jet().m();
    }

    inline float DeltaR() const {
        return sextetJet().delta_R(doublet_jet());
    }

    inline float DeltaRap() const {
        return sextetJet().rap() - doublet_jet().rap();
    }

    inline float DeltaPhi() const {
        return sextetJet().delta_phi_to(doublet_jet());
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
        return doublet().Singlet1().user_info<analysis::JetInfo>().Bdt() + doublet().Singlet2().user_info<analysis::JetInfo>().Bdt() + sextet().triplet1().singlet().user_info<analysis::JetInfo>().Bdt() + sextet().triplet2().singlet().user_info<analysis::JetInfo>().Bdt();
    }

    inline float PairBottomBdt() const {
        return doublet().Singlet1().user_info<analysis::JetInfo>().Bdt() + doublet().Singlet2().user_info<analysis::JetInfo>().Bdt();
    }
//
//     inline void SetJetNumber(const int NewJetNumber) {
//         event_structM.JetNumber = NewJetNumber;
//     }
//
//     inline void SetBottomNumber(const int NewBottomNumber) {
//         event_structM.BottomNumber = NewBottomNumber;
//     }
//
//     inline void SetLeptonNumber(const int NewLeptonNumber) {
//         event_structM.LeptonNumber = NewLeptonNumber;
//     }
//
//     inline float ScalarHt() const {
//         return event_structM.ScalarHt;
//     }
//
//     inline int JetNumber()const {
//         return event_structM.JetNumber;
//     }
//
//     inline int BottomNumber()const {
//         return event_structM.BottomNumber;
//     }
//
//     inline int LeptonNumber()const {
//         return event_structM.LeptonNumber;
//     }
//
//     inline EventStruct event_struct()const {
//         return event_structM;
//     }
//
//     inline void Setevent_struct(const EventStruct &Newevent_struct) {
//         event_structM = Newevent_struct;
//     }

//     EventStruct event_structM;

    inline float GetDeltaR1() const {
        return sextetJet().delta_R(doubletM.Singlet1());
    }

    inline float GetDeltaR2() const {
        return sextetJet().delta_R(doubletM.Singlet2());
    }

    inline float GetDeltaPhi1() const {
        return sextetJet().delta_phi_to(doubletM.Singlet1());
    }

    inline float GetDeltaPhi2() const {
        return sextetJet().delta_phi_to(doubletM.Singlet2());
    }

    inline float GetDeltaRap1() const {
        return (sextetJet().rap() - doubletM.Singlet1().rap());
    }

    inline float GetDeltaRap2() const {
        return (sextetJet().rap() - doubletM.Singlet2().rap());
    }

    inline float GetDeltaPt1() const {
        return (sextetJet().pt() - doubletM.Singlet1().pt());
    }

    inline float GetDeltaPt2() const {
        return (sextetJet().pt() - doubletM.Singlet2().pt());
    }


protected:

    virtual inline std::string ClassName() const {
        return "HOctet";
    }

private:

    analysis::Sextet sextetM;

    analysis::Doublet doubletM;

};

#endif
