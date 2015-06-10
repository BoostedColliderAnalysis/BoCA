# pragma once

# include "Sextet.hh"

namespace analysis {

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class Octet62 : public Multiplet<analysis::Sextet,analysis::Doublet>
{

public:

  using Multiplet<analysis::Sextet,analysis::Doublet>::Multiplet;

    bool overlap() const;

    bool overlap(const fastjet::PseudoJet &jet) const;

    inline analysis::Sextet Sextet()const {
        return multiplet_1_;
    }

    inline analysis::Doublet Doublet() const {
        return multiplet_2_;
    }

    inline float HbDeltaDeltaR() const {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }

    inline float HbDeltaDeltaRap() const {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }

    inline float HbDeltaDeltaPhi() const {
        return Object::DeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }

    inline float BottomBdt() const {
        return Doublet().Singlet1().user_info<JetInfo>().Bdt() + Doublet().Singlet2().user_info<JetInfo>().Bdt() + Sextet().Triplet1().SingletJet().user_info<JetInfo>().Bdt() + Sextet().Triplet2().SingletJet().user_info<JetInfo>().Bdt();
    }

    inline float PairBottomBdt() const {
        return Doublet().Singlet1().user_info<JetInfo>().Bdt() + Doublet().Singlet2().user_info<JetInfo>().Bdt();
    }

    inline float GetDeltaR1() const {
        return Sextet().Jet().delta_R(Doublet().Singlet1());
    }

    inline float GetDeltaR2() const {
        return Sextet().Jet().delta_R(Doublet().Singlet2());
    }

    inline float GetDeltaPhi1() const {
        return Sextet().Jet().delta_phi_to(Doublet().Singlet1());
    }

    inline float GetDeltaPhi2() const {
        return Sextet().Jet().delta_phi_to(Doublet().Singlet2());
    }

    inline float GetDeltaRap1() const {
        return (Sextet().Jet().rap() - Doublet().Singlet1().rap());
    }

    inline float GetDeltaRap2() const {
        return (Sextet().Jet().rap() - Doublet().Singlet2().rap());
    }

    inline float GetDeltaPt1() const {
        return (Sextet().Jet().pt() - Doublet().Singlet1().pt());
    }

    inline float GetDeltaPt2() const {
        return (Sextet().Jet().pt() - Doublet().Singlet2().pt());
    }

protected:

    virtual inline std::string ClassName() const {
        return "Octet62";
    }

private:

};

}
