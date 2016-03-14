/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Singlet.hh"
#include "SubJettiness.hh"
#include "Particle.hh"

namespace boca
{

class Multiplet : public Identification
{

public:

    void SetLeptonPt(Momentum const& lepton_pt);

    void SetLeptonDeltaR(Angle const& lepton_delta_r);

    Momentum LeptonPt() const;

    Angle LeptonDeltaR() const;

    boca::Singlet const& singlet() const;

    boca::Jet Jet() const;

    boca::Mass Mass() const;

    Momentum Pt() const;

    Angle Rap() const;

    Angle Phi() const;

    template<typename Multiplet_>
    using NotJet = typename std::enable_if < !std::is_same<Multiplet_, boca::Jet>::value && !std::is_same<Multiplet_, boca::PseudoJet>::value  && !std::is_same<Multiplet_, boca::Particle>::value>::type;

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaPhiTo(Multiplet_ const& multiplet) const {
        return Jet().DeltaPhiTo(multiplet.Jet());
    }

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaRTo(Multiplet_ const& multiplet) const {
        return Jet().DeltaRTo(multiplet.Jet());
    }

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaRapTo(Multiplet_ const& multiplet) const {
        return Jet().DeltaRapTo(multiplet.Jet());
    }

    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Vector2<Angle> DeltaTo(Multiplet_ const& multiplet) const {
        return Jet().DeltaTo(multiplet.Jet());
    }

    Angle DeltaPhiTo(PseudoJet const& jet) const {
      return Jet().DeltaPhiTo(jet);
    }

    Angle DeltaRTo(PseudoJet const& jet) const {
      return Jet().DeltaRTo(jet);
    }

    Angle DeltaRapTo(PseudoJet const& jet) const {
      return Jet().DeltaRapTo(jet);
    }

    Vector2<Angle> DeltaTo(PseudoJet const& jet) const {
      return Jet().DeltaTo(jet);
    }

    void SetSubJettiness();

    boca::SubJettiness SubJettiness() const;

protected:

    void SetSinglet(boca::Singlet const& singlet) const;

    virtual void SetSinglet() const = 0;

    void SetPlainJet(boca::Jet const& jet) const;

    virtual void SetPlainJet() const = 0;

private:

    boca::SubJettiness sub_jettiness_;

    Momentum lepton_pt_ = 0_eV;

    Angle lepton_delta_r_ = 0_rad;

    mutable boca::Singlet singlet_;

    mutable boca::Jet jet_;

    mutable bool has_singlet_ = false;

    mutable bool has_jet_ = false;

};

}
