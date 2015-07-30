#pragma once

#include "Sextet.hh"
#include "Quintet.hh"
#include "Quartet.hh"

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

    float HbDeltaDeltaR() const {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }

    float HbDeltaDeltaRap() const {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }

    float HbDeltaDeltaPhi() const {
        return ::analysis::DeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }

    float BottomBdt() const {
        return (Doublet().Singlet1().Jet().user_info<JetInfo>().Bdt() + Doublet().Singlet2().Jet().user_info<JetInfo>().Bdt() + Sextet().Triplet1().Singlet().Jet().user_info<JetInfo>().Bdt() + Sextet().Triplet2().Singlet().Jet().user_info<JetInfo>().Bdt()) / 4;
    }

    float PairBottomBdt() const {
        return (Doublet().Singlet1().Jet().user_info<JetInfo>().Bdt() + Doublet().Singlet2().Jet().user_info<JetInfo>().Bdt()) / 2;
    }

    float GetDeltaR1() const {
        return Sextet().Jet().delta_R(Doublet().Singlet1().Jet());
    }

    float GetDeltaR2() const {
        return Sextet().Jet().delta_R(Doublet().Singlet2().Jet());
    }

    float GetDeltaPhi1() const {
        return Sextet().Jet().delta_phi_to(Doublet().Singlet1().Jet());
    }

    float GetDeltaPhi2() const {
        return Sextet().Jet().delta_phi_to(Doublet().Singlet2().Jet());
    }

    float GetDeltaRap1() const {
        return (Sextet().Jet().rap() - Doublet().Singlet1().Jet().rap());
    }

    float GetDeltaRap2() const {
        return (Sextet().Jet().rap() - Doublet().Singlet2().Jet().rap());
    }

    float GetDeltaPt1() const {
        return (Sextet().Jet().pt() - Doublet().Singlet1().Jet().pt());
    }

    float GetDeltaPt2() const {
        return (Sextet().Jet().pt() - Doublet().Singlet2().Jet().pt());
    }

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet44 : public analysis::Multiplet<analysis::Quartet31, analysis::Quartet31> {

public:

  using analysis::Multiplet<analysis::Quartet31, analysis::Quartet31>::Multiplet;

  analysis::Quartet31& Quartet1() const;

  analysis::Quartet31& Quartet2() const;

  float BottomBdt() const;

  float PairBottomBdt() const;

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet53 : public analysis::Multiplet<analysis::Quintet, analysis::Triplet> {

public:

  using analysis::Multiplet<analysis::Quintet, analysis::Triplet>::Multiplet;

  analysis::Quintet& Quintet() const;

  analysis::Triplet& Triplet() const;

};

}