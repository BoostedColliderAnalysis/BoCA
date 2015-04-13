# ifndef HSextetEvent_hh
# define HSextetEvent_hh

# include "HSextet.hh"

struct HEventStruct {

    int LeptonNumber = 0;
    int JetNumber = 0;
    int BottomNumber = 0;
    float ScalarHt = 0;

};

class HSextetEventPrivate;

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HSextetEvent : public hanalysis::HTag
{

public:

    HSextetEvent(const hanalysis::HSextet &NewSextet);

    HSextetEvent(const hanalysis::HSextet &NewSextet, const HEventStruct &NewEventStruct);

    inline hanalysis::HSextet Sextet()const {
        return SextetM;
    }

    inline fastjet::PseudoJet SextetJet() const {
        return SextetM.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return SextetJet() + RestJet();
    }

    inline float Ht() const {
        float ht = Sextet().Ht();
        for (const auto & jet : Jets) ht += jet.pt();
        return ht;
    }

    inline void SetScalarHt(const float NewScalarHt) {
        EventM.ScalarHt = NewScalarHt;
    }

    inline void SetJetNumber(const int NewJetNumber) {
        EventM.JetNumber = NewJetNumber;
    }

    inline void SetBottomNumber(const int NewBottomNumber) {
        EventM.BottomNumber = NewBottomNumber;
    }

    inline void SetLeptonNumber(const int NewLeptonNumber) {
        EventM.LeptonNumber = NewLeptonNumber;
    }

    inline float ScalarHt() const {
        return EventM.ScalarHt;
    }

    inline int JetNumber()const {
        return EventM.JetNumber;
    }

    inline int BottomNumber()const {
        return EventM.BottomNumber;
    }

    inline int LeptonNumber()const {
        return EventM.LeptonNumber;
    }

    inline HEventStruct EventStruct()const {
        return EventM;
    }

    inline void SetEventStruct(const HEventStruct &NewEventStruct) {
        EventM = NewEventStruct;
    }

    HEventStruct EventM;

    inline void AddRestJet(const fastjet::PseudoJet &NewJet) {
        SetBdt(Bdt() * (JetNumber() + 1));
        Jets.push_back(NewJet);
        SetBdt(Bdt() + NewJet.user_info<hanalysis::HJetInfo>().Bdt());
        SetBdt(Bdt() / (JetNumber() + 1));
    }

    inline int RestNumber() const {
        return Jets.size();
    }

    fastjet::PseudoJet RestJet() const {
        fastjet::PseudoJet jet;
        return std::accumulate(Jets.begin(), Jets.end(), jet);
    }

    float RestHt() const {
        float ht = 0;
        for (const auto & jet : Jets)ht += jet.pt();
        return ht;
    }

    float RestBdt() const {
        if (RestNumber() < 1) return 0;
        float bdt = 0;
        for (const auto & jet : Jets)bdt += jet.user_info<hanalysis::HJetInfo>().Bdt();
        return bdt / RestNumber();
    }

    void SetLeptons(const HJets &NewLeptons) {
        LeptonsM = NewLeptons;
    }

    float LeptonHt() const {
        float ht = 0;
        for (const auto & jet : LeptonsM)ht += jet.pt();
        return ht;
    }

    float DeltaPt() const {
        return SextetJet().pt() - RestJet().pt();
    }

    float DeltaPhi() const {
        return SextetJet().delta_phi_to(RestJet());
    }

    float DeltaRap() const {
        float NewDeltaRap = SextetJet().rap() - RestJet().rap();
        if (std::abs(NewDeltaRap) > 100) NewDeltaRap = 0;
        return NewDeltaRap;
    }

    float DeltaR() const {
        float NewDeltaR = SextetJet().delta_R(RestJet());
        if (std::abs(NewDeltaR) > 100) NewDeltaR = 0;
        return NewDeltaR;
    }

    float DeltaHt() const {
      return Sextet().Ht() - RestJet().pt();
    }

    float DeltaM() const {
      return SextetJet().m() - RestJet().m();
    }


protected:

    virtual inline std::string ClassName() const {
        return "HSextetEvent";
    }

private:

    hanalysis::HSextet SextetM;

    HJets Jets;

    HJets LeptonsM;

};

#endif
