#pragma once

#include "ThreeBody.hh"
#include "Sextet.hh"
#include "Quintet.hh"
#include "Quartet.hh"

namespace analysis {

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class Octet62 : public TwoBody<::analysis::Sextet, ::analysis::Doublet> {

public:

    using TwoBody<::analysis::Sextet, ::analysis::Doublet>::TwoBody;

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
class Octet44 : public analysis::TwoBody<analysis::Quartet31, analysis::Quartet31> {

public:

  using analysis::TwoBody<analysis::Quartet31, analysis::Quartet31>::TwoBody;

  analysis::Quartet31& Quartet1() const;

  analysis::Quartet31& Quartet2() const;

  float BottomBdt() const;

  float PairBottomBdt() const;

};

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet53 : public analysis::TwoBody<analysis::Quintet, analysis::Triplet> {

public:

  using analysis::TwoBody<analysis::Quintet, analysis::Triplet>::TwoBody;

  analysis::Quintet& Quintet() const;

  analysis::Triplet& Triplet() const;

};

class Octet332 : public analysis::ThreeBody<analysis::Triplet,analysis::Triplet,analysis::Doublet>{

public:

  using analysis::ThreeBody<analysis::Triplet,analysis::Triplet,analysis::Doublet>::ThreeBody;

  analysis::Triplet& Triplet1() const{return Multiplet1();};

  analysis::Triplet& Triplet2() const{return Multiplet2();};

  analysis::Doublet& Doublet() const{return Multiplet3();};

  float PairRap() const {
    return Triplet1().Jet().rap() - Triplet2().Jet().rap();
  }

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
    return (Doublet().Singlet1().Jet().user_info<JetInfo>().Bdt() + Doublet().Singlet2().Jet().user_info<JetInfo>().Bdt() + Triplet1().Singlet().Jet().user_info<JetInfo>().Bdt() + Triplet2().Singlet().Jet().user_info<JetInfo>().Bdt()) / 4;
  }

  float PairBottomBdt() const {
    return (Doublet().Singlet1().Jet().user_info<JetInfo>().Bdt() + Doublet().Singlet2().Jet().user_info<JetInfo>().Bdt()) / 2;
  }

  float GetDeltaR1() const {
    return Jet().delta_R(Doublet().Singlet1().Jet());
  }

  float GetDeltaR2() const {
    return Jet().delta_R(Doublet().Singlet2().Jet());
  }

  float GetDeltaPhi1() const {
    return Jet().delta_phi_to(Doublet().Singlet1().Jet());
  }

  float GetDeltaPhi2() const {
    return Jet().delta_phi_to(Doublet().Singlet2().Jet());
  }

  float GetDeltaRap1() const {
    return (Jet().rap() - Doublet().Singlet1().Jet().rap());
  }

  float GetDeltaRap2() const {
    return (Jet().rap() - Doublet().Singlet2().Jet().rap());
  }

  float GetDeltaPt1() const {
    return (Jet().pt() - Doublet().Singlet1().Jet().pt());
  }

  float GetDeltaPt2() const {
    return (Jet().pt() - Doublet().Singlet2().Jet().pt());
  }

};

}
