# pragma once

# include "Quartet31.hh"

struct EventStructCharged {

    int lepton_number = 0;
    int jet_number = 0;
    int bottom_number = 0;
    float scalar_ht = 0;
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
class Octet44 : public analysis::Identification
{

public:

    Octet44() {};

    Octet44(const analysis::Quartet31 &quartet_1, const analysis::Quartet31 &quartet_2);

    Octet44(const analysis::Quartet31 &quartet_1, const analysis::Quartet31 &quartet_2, const EventStructCharged &global_observables);

    inline analysis::Quartet31 quartet1()const {
        return quartet_1_;
    }

    inline analysis::Quartet31 quartet2() const {
        return quartet_2_;
    }
    inline fastjet::PseudoJet Getquartet1Jet() const {
        return quartet_1_.Jet();
    }

    inline fastjet::PseudoJet Getquartet2Jet() const {
        return quartet_2_.Jet();
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

    inline EventStructCharged global_observables()const {
        return global_observables_;
    }

    inline void Setglobal_observables(const EventStructCharged &global_observables) {
        global_observables_ = global_observables;
    }

    analysis::Quartet31 SubMultiplet1() const {
      return quartet_1_;
    }

    analysis::Quartet31 SubMultiplet2() const {
      return quartet_2_;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Octet44";
    }

private:

    analysis::Quartet31 quartet_1_;

    analysis::Quartet31 quartet_2_;

    EventStructCharged global_observables_;

};

