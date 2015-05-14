# ifndef HSextetevent_hh
# define HSextetevent_hh

# include "HSextet.hh"

struct EventStruct {

    int LeptonNumber = 0;
    int JetNumber = 0;
    int BottomNumber = 0;
    float ScalarHt = 0;

};

class HSexteteventPrivate;

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HSextetevent : public hanalysis::HTag
{

public:

    HSextetevent(const hanalysis::HSextet &NewSextet);

    HSextetevent(const hanalysis::HSextet &NewSextet, const EventStruct &NeweventStruct);

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
        for (const auto & jet : jets_)  ht += jet.pt();
        return ht;
    }

    inline void SetScalarHt(const float NewScalarHt) {
        eventM.ScalarHt = NewScalarHt;
    }

    inline void SetJetNumber(const int NewJetNumber) {
        eventM.JetNumber = NewJetNumber;
    }

    inline void SetBottomNumber(const int NewBottomNumber) {
        eventM.BottomNumber = NewBottomNumber;
    }

    inline void SetLeptonNumber(const int NewLeptonNumber) {
        eventM.LeptonNumber = NewLeptonNumber;
    }

    inline float ScalarHt() const {
        return eventM.ScalarHt;
    }

    inline int JetNumber()const {
        return eventM.JetNumber;
    }

    inline int BottomNumber()const {
        return eventM.BottomNumber;
    }

    inline int LeptonNumber()const {
        return eventM.LeptonNumber;
    }

    inline EventStruct eventStruct()const {
        return eventM;
    }

    inline void SeteventStruct(const EventStruct &NeweventStruct) {
        eventM = NeweventStruct;
    }

    EventStruct eventM;

    inline void AddRestJet(const fastjet::PseudoJet &NewJet) {
        SetBdt(Bdt() * (JetNumber() + 1));
        jets_.emplace_back(NewJet);
        SetBdt(Bdt() + NewJet.user_info<hanalysis::JetInfo>().Bdt());
        SetBdt(Bdt() / (JetNumber() + 1));
    }

    inline int RestNumber() const {
        return jets_.size();
    }

    fastjet::PseudoJet RestJet() const {
        fastjet::PseudoJet jet;
        return std::accumulate(jets_.begin(), jets_.end(), jet);
    }

    float RestHt() const {
        float ht = 0;
        for (const auto & jet : jets_) ht += jet.pt();
        return ht;
    }

    float RestBdt() const {
        if (RestNumber() < 1) return 0;
        float bdt = 0;
        for (const auto & jet : jets_) bdt += jet.user_info<hanalysis::JetInfo>().Bdt();
        return bdt / RestNumber();
    }

    void SetLeptons(const Jets &NewLeptons) {
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
        return "HSextetevent";
    }

private:

    hanalysis::HSextet SextetM;

    Jets jets_;

    Jets LeptonsM;

};

#endif
