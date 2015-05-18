# ifndef EventMultiplet_hh
# define EventMultiplet_hh

# include "HOctet44.hh"
// # include "HOctet.hh"

struct EventStruct {

    int LeptonNumber = 0;
    int JetNumber = 0;
    int BottomNumber = 0;
    float ScalarHt = 0;
    float MissingEt = 0;
//     int TrackNumber =0;

};


/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
template <typename TMultiplet>
class EventMultiplet : public analysis::Identification
{

public:

    EventMultiplet(const TMultiplet &NewOctet) {
        Octet44M = NewOctet;
        SetBdt(Octet44M.Bdt());
        SetTag(Octet44M.Tag());

    };

    EventMultiplet(const TMultiplet &NewOctet, const EventStruct &Newevent_struct) {
        Octet44M = NewOctet;
        eventM = Newevent_struct;
        SetBdt(Octet44M.Bdt());
        SetTag(Octet44M.Tag());
    };

    inline TMultiplet Octet()const {
        return Octet44M;
    }

    inline fastjet::PseudoJet OctetJet() const {
        return Octet44M.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return OctetJet() + RestJet();
    }

    inline float Ht() const {
        float ht = Octet().Ht();
        for (const auto & jet : RestJets) ht += jet.pt();
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

    inline float MissingEt() const {
      return eventM.MissingEt;
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

    inline EventStruct event_struct()const {
        return eventM;
    }

    inline void Setevent_struct(const EventStruct &Newevent_struct) {
        eventM = Newevent_struct;
    }

    EventStruct eventM;

    inline void SetTotalJets(const Jets &NewJets) {
        AllJets = NewJets;
        std::sort(AllJets.begin(), AllJets.end(), analysis::SortByBdt());
    }

    inline void SetSubJets(const Jets &NewJets) {
        SubJets = NewJets;
        std::sort(SubJets.begin(), SubJets.end(), analysis::SortByBdt());
    }

//     inline float TotalBottomBdt(const int Sum) const {
//         if (Sum < 0) return 0;
//         if (AllJets.size() < Sum) return 0;
//         float BdtSum = 0;
//         for (int Number = 0; Number < Sum; ++Number) BdtSum += AllJets.at(Number).user_info<analysis::JetInfo>().Bdt();
//         return BdtSum / Sum;
//     }

    inline float BottomBdt(const unsigned Number) const {
        if (Number < 0) return 0;
        if (AllJets.size() < Number) return 0;
        return AllJets.at(Number - 1).user_info<analysis::JetInfo>().Bdt();
    }

    inline float BottomBdt(const unsigned Number1, const unsigned Number2) const {
        return (BottomBdt(Number1) + BottomBdt(Number2)) / 2;
    }

    inline float SubBottomBdt(const unsigned Sum) const {
        if (Sum < 0) return 0;
        if (SubJets.size() < Sum) return 0;
        return SubJets.at(Sum - 1).user_info<analysis::JetInfo>().Bdt();
    }

    inline float SubBottomBdt(const unsigned Number1, const unsigned Number2) const {
        return (SubBottomBdt(Number1) + SubBottomBdt(Number2)) / 2;
    }

    inline void AddRestJet(const fastjet::PseudoJet &NewJet) {
        SetBdt(Bdt() * (JetNumber() + 1));
        RestJets.emplace_back(NewJet);
        SetBdt(Bdt() + NewJet.user_info<analysis::JetInfo>().Bdt());
        SetBdt(Bdt() / (JetNumber() + 1));
    }

    inline int RestNumber() const {
        return RestJets.size();
    }

    fastjet::PseudoJet RestJet() const {
        fastjet::PseudoJet jet;
        return std::accumulate(RestJets.begin(), RestJets.end(), jet);
    }

    float RestHt() const {
        float ht = 0;
        for (const auto & jet : RestJets)ht += jet.pt();
        return ht;
    }

    float RestBdt() const {
        if (RestNumber() < 1) return 0;
        float bdt = 0;
        for (const auto & jet : RestJets)bdt += jet.user_info<analysis::JetInfo>().Bdt();
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
        return OctetJet().pt() - RestJet().pt();
    }

    float DeltaHt() const {
        return Octet().Ht() - RestHt();
    }

    float DeltaM() const {
        return OctetJet().m() - RestJet().m();
    }

    float DeltaPhi() const {
        return OctetJet().delta_phi_to(RestJet());
    }

    float DeltaRap() const {
        float NewDeltaRap = OctetJet().rap() - RestJet().rap();
        if (std::abs(NewDeltaRap) > 100) NewDeltaRap = 0;
        return NewDeltaRap;
    }

    float DeltaR() const {
        float NewDeltaR = OctetJet().delta_R(RestJet());
        if (std::abs(NewDeltaR) > 100) NewDeltaR = 0;
        return NewDeltaR;
    }

protected:

    virtual inline std::string ClassName() const {
        return "EventMultiplet";
    }

private:

    TMultiplet Octet44M;

    Jets RestJets;

    Jets AllJets;

    Jets SubJets;

    Jets LeptonsM;

};

#endif
