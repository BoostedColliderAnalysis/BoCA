# pragma once

# include "Quartet31.hh"

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet44 : public analysis::Identification
{

public:

    Octet44() {};

    Octet44(const analysis::Quartet31 &quartet_1, const analysis::Quartet31 &quartet_2);

    bool overlap() const;

    bool overlap(const fastjet::PseudoJet &jet) const;

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

};

