#pragma once

#include "Sextet.hh"

namespace analysis {

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class Octet62 : public Multiplet<::analysis::Sextet, ::analysis::Doublet> {

public:

    using Multiplet<::analysis::Sextet, ::analysis::Doublet>::Multiplet;

    analysis::Sextet& Sextet() const;

    analysis::Doublet& Doublet() const;

    float HbDeltaDeltaR() const
    {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }

    float HbDeltaDeltaRap() const
    {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }

    float HbDeltaDeltaPhi() const
    {
        return ::analysis::DeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }

    float BottomBdt() const
    {
        return Doublet().SingletJet1().user_info<JetInfo>().Bdt() + Doublet().SingletJet2().user_info<JetInfo>().Bdt() + Sextet().Triplet1().Singlet().Jet().user_info<JetInfo>().Bdt() + Sextet().Triplet2().Singlet().Jet().user_info<JetInfo>().Bdt();
    }

    float PairBottomBdt() const
    {
        return Doublet().SingletJet1().user_info<JetInfo>().Bdt() + Doublet().SingletJet2().user_info<JetInfo>().Bdt();
    }

    float GetDeltaR1() const
    {
        return Sextet().Jet().delta_R(Doublet().SingletJet1());
    }

    float GetDeltaR2() const
    {
        return Sextet().Jet().delta_R(Doublet().SingletJet2());
    }

    float GetDeltaPhi1() const
    {
        return Sextet().Jet().delta_phi_to(Doublet().SingletJet1());
    }

    float GetDeltaPhi2() const
    {
        return Sextet().Jet().delta_phi_to(Doublet().SingletJet2());
    }

    float GetDeltaRap1() const
    {
        return (Sextet().Jet().rap() - Doublet().SingletJet1().rap());
    }

    float GetDeltaRap2() const
    {
        return (Sextet().Jet().rap() - Doublet().SingletJet2().rap());
    }

    float GetDeltaPt1() const
    {
        return (Sextet().Jet().pt() - Doublet().SingletJet1().pt());
    }

    float GetDeltaPt2() const
    {
        return (Sextet().Jet().pt() - Doublet().SingletJet2().pt());
    }

};

}
