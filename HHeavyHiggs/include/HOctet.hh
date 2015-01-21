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

class HOctetPrivate;

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HOctet : public hanalysis::HTag
{

public:

    HOctet() {};

    HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet);

    HOctet(const hanalysis::HSextet &NewSextet, const hanalysis::HDoublet &NewDoublet, const HEventStruct &NewEventStruct);


    inline hanalysis::HSextet Sextet()const {
        return SextetM;
    }

    inline hanalysis::HDoublet Doublet() const {
        return DoubletM;
    }

    inline fastjet::PseudoJet SextetJet() const {
        return SextetM.Jet();
    }

    inline fastjet::PseudoJet DoubletJet() const {
        return DoubletM.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return SextetJet() + DoubletJet();
    }

    inline float Ht() const {
        return SextetM.Ht() + DoubletM.Ht();
    }

    inline float DeltaPt() const {
        return SextetJet().pt() - DoubletJet().pt();
    }

    inline float DeltaR() const {
        return SextetJet().delta_R(DoubletJet());
    }

    inline float DeltaRap() const {
        return SextetJet().rap() - DoubletJet().rap();
    }

    inline float DeltaPhi() const {
        return SextetJet().delta_phi_to(DoubletJet());
    }

    inline float HbDeltaDeltaR() const {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }

    inline float HbDeltaDeltaRap() const {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }

    inline float HbDeltaDeltaPhi() const {
        return HObject::GetDeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }

    inline void SetScalarHt(const float NewScalarHt) {
        EventStructM.ScalarHt = NewScalarHt;
    }

    inline void SetJetNumber(const int NewJetNumber) {
        EventStructM.JetNumber = NewJetNumber;
    }

    inline void SetBottomNumber(const int NewBottomNumber) {
        EventStructM.BottomNumber = NewBottomNumber;
    }

    inline void SetLeptonNumber(const int NewLeptonNumber) {
        EventStructM.LeptonNumber = NewLeptonNumber;
    }

    inline float ScalarHt() const {
        return EventStructM.ScalarHt;
    }

    inline int JetNumber()const {
        return EventStructM.JetNumber;
    }

    inline int BottomNumber()const {
        return EventStructM.BottomNumber;
    }

    inline int LeptonNumber()const {
        return EventStructM.LeptonNumber;
    }

    inline HEventStruct EventStruct()const {
        return EventStructM;
    }

    inline void SetEventStruct(const HEventStruct &NewEventStruct) {
        EventStructM = NewEventStruct;
    }

    HEventStruct EventStructM;

    inline float GetDeltaR1() const {
        return SextetJet().delta_R(DoubletM.Singlet1());
    }

    inline float GetDeltaR2() const {
        return SextetJet().delta_R(DoubletM.Singlet2());
    }

    inline float GetDeltaPhi1() const {
        return SextetJet().delta_phi_to(DoubletM.Singlet1());
    }

    inline float GetDeltaPhi2() const {
        return SextetJet().delta_phi_to(DoubletM.Singlet2());
    }

    inline float GetDeltaRap1() const {
        return (SextetJet().rap() - DoubletM.Singlet1().rap());
    }

    inline float GetDeltaRap2() const {
        return (SextetJet().rap() - DoubletM.Singlet2().rap());
    }

    inline float GetDeltaPt1() const {
        return (SextetJet().pt() - DoubletM.Singlet1().pt());
    }

    inline float GetDeltaPt2() const {
        return (SextetJet().pt() - DoubletM.Singlet2().pt());
    }


protected:

    virtual inline std::string ClassName() const {
        return "HOctet";
    }

private:

    hanalysis::HSextet SextetM;

    hanalysis::HDoublet DoubletM;

};

#endif
