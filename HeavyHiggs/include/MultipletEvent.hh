# pragma once

# include "Singlet.hh"
# include "Event.hh"

namespace analysis
{

class GlobalObservables
{
public:
    GlobalObservables() {}
    GlobalObservables(Event &event) {
        lepton_number_ = event.Leptons().leptons().size();
        jet_number_ = event.Hadrons().Jets().size();
//         bottom_number_ = event.Hadrons().BottomJets().size();
        scalar_ht_ = event.Hadrons().ScalarHt();
        missing_et_ = event.Hadrons().MissingEt().pt();
    }
    int lepton_number()const {
        return lepton_number_;
    }
    int jet_number()const {
        return jet_number_;
    }
    int bottom_number()const {
        return bottom_number_;
    }
    float scalar_ht()const {
        return scalar_ht_;
    }
    float missing_et()const {
        return missing_et_;
    }
private:
    int lepton_number_;
    int jet_number_;
    int bottom_number_;
    float scalar_ht_;
    float missing_et_;
};


/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
template <typename Multiplet>
class MultipletEvent : public Identification
{

public:

    MultipletEvent(const Multiplet &multiplet) {
        multiplet_ = multiplet;
        SetBdt(multiplet_.Bdt());
        SetTag(multiplet_.Tag());

    }

    MultipletEvent(const Multiplet &multiplet, const GlobalObservables &global_observables) {
        multiplet_ = multiplet;
        global_observables_ = global_observables;
        SetBdt(multiplet_.Bdt());
        SetTag(multiplet_.Tag());
    }

    inline Multiplet multiplet()const {
        return multiplet_;
    }

    inline fastjet::PseudoJet octetJet() const {
        return multiplet_.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return octetJet() + RestJet();
    }

    inline float Ht() const {
        float ht = multiplet().Ht();
        for (const auto & jet : rest_jets_) ht += jet.pt();
        return ht;
    }

    inline void SetScalarHt(const float scalar_ht) {
        global_observables_.scalar_ht = scalar_ht;
    }

    inline void SetJetNumber(const int jet_number) {
        global_observables_.jet_number = jet_number;
    }

    inline void SetBottomNumber(const int bottom_number) {
        global_observables_.bottom_number = bottom_number;
    }

    inline void SetLeptonNumber(const int lepton_number) {
        global_observables_.lepton_number = lepton_number;
    }

    inline float ScalarHt() const {
        return global_observables_.scalar_ht();
    }

    inline float MissingEt() const {
        return global_observables_.missing_et();
    }

    inline int JetNumber()const {
        return global_observables_.jet_number();
    }

    inline int BottomNumber()const {
        return global_observables_.bottom_number();
    }

    inline int LeptonNumber()const {
        return global_observables_.lepton_number();
    }

    inline GlobalObservables &global_observables()const {
        return global_observables_;
    }

    inline void Setglobal_observables(const GlobalObservables &global_observables) {
        global_observables_ = global_observables;
    }

    inline void SetTotalJets(const Jets &jets) {
        all_jets_ = jets;
        std::sort(all_jets_.begin(), all_jets_.end(), SortByBdt());
    }

    inline void SetSubJets(const Jets &jets) {
        sub_jets_ = jets;
        std::sort(sub_jets_.begin(), sub_jets_.end(), SortByBdt());
    }

    inline float BottomBdt(const unsigned number) const {
        if (number < 0) return 0;
        if (all_jets_.size() < number) return 0;
        return all_jets_.at(number - 1).user_info<JetInfo>().Bdt();
    }

    inline float BottomBdt(const unsigned number_1, const unsigned number_2) const {
        return (BottomBdt(number_1) + BottomBdt(number_2)) / 2;
    }

    inline float SubBottomBdt(const unsigned sum) const {
        if (sum < 0) return 0;
        if (sub_jets_.size() < sum) return 0;
        return sub_jets_.at(sum - 1).user_info<JetInfo>().Bdt();
    }

    inline float SubBottomBdt(const unsigned number_1, const unsigned number_2) const {
        return (SubBottomBdt(number_1) + SubBottomBdt(number_2)) / 2;
    }

    inline void AddRestJet(const fastjet::PseudoJet &jet) {
        if (multiplet_.overlap(jet)) return;
        SetBdt(Bdt() * (JetNumber() + 1));
        rest_jets_.emplace_back(jet);
        SetBdt(Bdt() + jet.user_info<JetInfo>().Bdt());
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
        for (const auto & jet : rest_jets_)bdt += jet.user_info<JetInfo>().Bdt();
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
        return octetJet().pt() - RestJet().pt();
    }

    float DeltaHt() const {
        return multiplet().Ht() - RestHt();
    }

    float DeltaM() const {
        return octetJet().m() - RestJet().m();
    }

    float DeltaPhi() const {
        return octetJet().delta_phi_to(RestJet());
    }

    float DeltaRap() const {
        float delta_rap = octetJet().rap() - RestJet().rap();
        if (std::abs(delta_rap) > 100) delta_rap = 0;
        return delta_rap;
    }

    float DeltaR() const {
        float delta_r = octetJet().delta_R(RestJet());
        if (std::abs(delta_r) > 100) delta_r = 0;
        return delta_r;
    }

    Multiplet SubMultiplet1() const {
        return multiplet_;
    }

    Singlet SubMultiplet2() const {
        return Singlet(RestJet());
    }

protected:

    virtual inline std::string ClassName() const {
        return "MultipletEvent";
    }

private:

    Multiplet multiplet_;

    Jets rest_jets_;

    Jets all_jets_;

    Jets sub_jets_;

    Jets leptons_;

    GlobalObservables global_observables_;

};

}
