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

//     bool Overlap() const;

//     bool Overlap(const fastjet::PseudoJet &jet) const;

    analysis::Sextet Sextet()const;

    analysis::Doublet Doublet() const;

    inline float HbDeltaDeltaR() const {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }

    inline float HbDeltaDeltaRap() const {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }

    inline float HbDeltaDeltaPhi() const {
        return analysis::DeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }

    inline float BottomBdt() const {
        return Doublet().SingletJet1().user_info<JetInfo>().Bdt() + Doublet().SingletJet2().user_info<JetInfo>().Bdt() + Sextet().Triplet1().SingletJet().user_info<JetInfo>().Bdt() + Sextet().Triplet2().SingletJet().user_info<JetInfo>().Bdt();
    }

    inline float PairBottomBdt() const {
        return Doublet().SingletJet1().user_info<JetInfo>().Bdt() + Doublet().SingletJet2().user_info<JetInfo>().Bdt();
    }

    inline float GetDeltaR1() const {
        return Sextet().Jet().delta_R(Doublet().SingletJet1());
    }

    inline float GetDeltaR2() const {
        return Sextet().Jet().delta_R(Doublet().SingletJet2());
    }

    inline float GetDeltaPhi1() const {
        return Sextet().Jet().delta_phi_to(Doublet().SingletJet1());
    }

    inline float GetDeltaPhi2() const {
        return Sextet().Jet().delta_phi_to(Doublet().SingletJet2());
    }

    inline float GetDeltaRap1() const {
        return (Sextet().Jet().rap() - Doublet().SingletJet1().rap());
    }

    inline float GetDeltaRap2() const {
        return (Sextet().Jet().rap() - Doublet().SingletJet2().rap());
    }

    inline float GetDeltaPt1() const {
        return (Sextet().Jet().pt() - Doublet().SingletJet1().pt());
    }

    inline float GetDeltaPt2() const {
        return (Sextet().Jet().pt() - Doublet().SingletJet2().pt());
    }

protected:

    virtual inline std::string ClassName() const {
        return "Octet62";
    }

private:

};

}
