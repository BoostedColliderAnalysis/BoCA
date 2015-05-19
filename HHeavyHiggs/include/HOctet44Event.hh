# pragma once

# include "Identification.hh"
# include "JetInfo.hh"

// namespace analysis{

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
template <typename Multiplet>
class EventMultiplet : public analysis::Identification
{

public:

    EventMultiplet(const Multiplet &octet) {
        octet_ = octet;
        SetBdt(octet_.Bdt());
        SetTag(octet_.Tag());

    };

    EventMultiplet(const Multiplet &octet, const EventStruct &Newevent_struct) {
        octet_ = octet;
        eventM = Newevent_struct;
        SetBdt(octet_.Bdt());
        SetTag(octet_.Tag());
    };

    inline Multiplet Octet()const {
        return octet_;
    }

    inline fastjet::PseudoJet OctetJet() const {
        return octet_.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return OctetJet() + RestJet();
    }

    inline float Ht() const {
        float ht = Octet().Ht();
        for (const auto & jet : rest_jets_) ht += jet.pt();
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
        all_jets_ = NewJets;
        std::sort(all_jets_.begin(), all_jets_.end(), analysis::SortByBdt());
    }

    inline void SetSubJets(const Jets &NewJets) {
        sub_jets_ = NewJets;
        std::sort(sub_jets_.begin(), sub_jets_.end(), analysis::SortByBdt());
    }

    inline float BottomBdt(const unsigned Number) const {
        if (Number < 0) return 0;
        if (all_jets_.size() < Number) return 0;
        return all_jets_.at(Number - 1).user_info<analysis::JetInfo>().Bdt();
    }

    inline float BottomBdt(const unsigned Number1, const unsigned Number2) const {
        return (BottomBdt(Number1) + BottomBdt(Number2)) / 2;
    }

    inline float SubBottomBdt(const unsigned Sum) const {
        if (Sum < 0) return 0;
        if (sub_jets_.size() < Sum) return 0;
        return sub_jets_.at(Sum - 1).user_info<analysis::JetInfo>().Bdt();
    }

    inline float SubBottomBdt(const unsigned Number1, const unsigned Number2) const {
        return (SubBottomBdt(Number1) + SubBottomBdt(Number2)) / 2;
    }

    inline void AddRestJet(const fastjet::PseudoJet &NewJet) {
        SetBdt(Bdt() * (JetNumber() + 1));
        rest_jets_.emplace_back(NewJet);
        SetBdt(Bdt() + NewJet.user_info<analysis::JetInfo>().Bdt());
        SetBdt(Bdt() / (JetNumber() + 1));
    }

    inline int RestNumber() const {
        return rest_jets_.size();
    }

    fastjet::PseudoJet RestJet() const {
        fastjet::PseudoJet jet;
        return std::accumulate(rest_jets_.begin(), rest_jets_.end(), jet);
    }

    float RestHt() const {
        float ht = 0;
        for (const auto & jet : rest_jets_)ht += jet.pt();
        return ht;
    }

    float RestBdt() const {
        if (RestNumber() < 1) return 0;
        float bdt = 0;
        for (const auto & jet : rest_jets_)bdt += jet.user_info<analysis::JetInfo>().Bdt();
        return bdt / RestNumber();
    }

    void SetLeptons(const Jets &NewLeptons) {
        leptons_ = NewLeptons;
    }

    float LeptonHt() const {
        float ht = 0;
        for (const auto & jet : leptons_)ht += jet.pt();
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

    Multiplet octet_;

    Jets rest_jets_;

    Jets all_jets_;

    Jets sub_jets_;

    Jets leptons_;

};

// }
