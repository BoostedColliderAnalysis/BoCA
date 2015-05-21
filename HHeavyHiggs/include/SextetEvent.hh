# pragma once

# include "Sextet.hh"

struct GlobalObservables {

    int lepton_number = 0;
    int jet_number = 0;
    int bottom_number = 0;
    float scalar_ht = 0;

};

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class SextetEvent : public analysis::Identification
{

public:

    SextetEvent(const analysis::Sextet &Newsextet);

    SextetEvent(const analysis::Sextet &Newsextet, const GlobalObservables &global_observables);

    inline analysis::Sextet sextet()const {
        return sextet_;
    }

    inline fastjet::PseudoJet sextetJet() const {
        return sextet_.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return sextetJet() + RestJet();
    }

    inline float Ht() const {
        float ht = sextet().Ht();
        for (const auto & jet : jets_)  ht += jet.pt();
        return ht;
    }

    inline void SetScalarHt(const float scalar_ht) {
        global_observables_.scalar_ht = scalar_ht;
    }

    inline void SetJetNumber(const int number) {
        global_observables_.jet_number = number;
    }

    inline void SetBottomNumber(const int number) {
        global_observables_.bottom_number = number;
    }

    inline void SetLeptonNumber(const int number) {
        global_observables_.lepton_number = number;
    }

    inline float ScalarHt() const {
        return global_observables_.scalar_ht;
    }

    inline int JetNumber()const {
        return global_observables_.jet_number;
    }

    inline int BottomNumber()const {
        return global_observables_.bottom_number;
    }

    inline int LeptonNumber()const {
        return global_observables_.lepton_number;
    }

    inline GlobalObservables global_observables()const {
        return global_observables_;
    }

    inline void SetEventStruct(const GlobalObservables &global_observables) {
        global_observables_ = global_observables;
    }

    GlobalObservables global_observables_;

    inline void AddRestJet(const fastjet::PseudoJet &jet) {
        SetBdt(Bdt() * (JetNumber() + 1));
        jets_.emplace_back(jet);
        SetBdt(Bdt() + jet.user_info<analysis::JetInfo>().Bdt());
        SetBdt(Bdt() / (JetNumber() + 1));
    }

    inline int RestNumber() const {
        return jets_.size();
    }

    fastjet::PseudoJet RestJet() const {
      return std::accumulate(jets_.begin(), jets_.end(), fastjet::PseudoJet());
    }

    float RestHt() const {
        float ht = 0;
        for (const auto & jet : jets_) ht += jet.pt();
        return ht;
    }

    float RestBdt() const {
        if (RestNumber() < 1) return 0;
        float bdt = 0;
        for (const auto & jet : jets_) bdt += jet.user_info<analysis::JetInfo>().Bdt();
        return bdt / RestNumber();
    }

    void SetLeptons(const Jets &leptons) {
        leptons_ = leptons;
    }

    float LeptonHt() const {
        float ht = 0;
        for (const auto & jet : leptons_)ht += jet.pt();
        return ht;
    }

    float DeltaPt() const {
        return sextetJet().pt() - RestJet().pt();
    }

    float DeltaPhi() const {
        return sextetJet().delta_phi_to(RestJet());
    }

    float DeltaRap() const {
        float delta_rap = sextetJet().rap() - RestJet().rap();
        if (std::abs(delta_rap) > 100) delta_rap = 0;
        return delta_rap;
    }

    float DeltaR() const {
        float delta_r = sextetJet().delta_R(RestJet());
        if (std::abs(delta_r) > 100) delta_r = 0;
        return delta_r;
    }

    float DeltaHt() const {
      return sextet().Ht() - RestJet().pt();
    }

    float DeltaM() const {
      return sextetJet().m() - RestJet().m();
    }


protected:

    virtual inline std::string ClassName() const {
        return "SextetEvent";
    }

private:

    analysis::Sextet sextet_;

    Jets jets_;

    Jets leptons_;

};
