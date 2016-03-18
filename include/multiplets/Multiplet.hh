/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Singlet.hh"
#include "SubJettiness.hh"
#include "ClosestLepton.hh"
#include "Particle.hh"
#include "Multiplets.hh"

namespace boca
{

class Multiplet : public Identification
{

public:

    void SetClosestLepton(std::vector<boca::Lepton> const& leptons);

    ClosestLepton Lepton() const;

    boca::Singlet const& ConstituentJet() const;

    boca::Jet Jet() const;

    boca::Mass Mass() const;

    Momentum Pt() const;

    Angle Rap() const;

    Angle Phi() const;

    template<typename Multiplet_>
    using NotJet = typename std::enable_if < !std::is_same<Multiplet_, boca::Jet>::value && !std::is_same<Multiplet_, boca::PseudoJet>::value && !std::is_same<Multiplet_, boca::Particle>::value >::type;

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

    Angle DeltaPhiTo(PseudoJet const& jet) const;

    Angle DeltaRTo(PseudoJet const& jet) const;

    Angle DeltaRapTo(PseudoJet const& jet) const;

    Vector2<Angle> DeltaTo(PseudoJet const& jet) const;

    std::vector<boca::Jet> Constituents() const;

    boca::SubJettiness SubJettiness() const;

protected:

    template<typename Multiplet_1_, typename Multiplet_2_>
    void SetConstituentJet(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2) const {
        constituent_jet_ = JoinConstituents(multiplet_1, multiplet_2);
        has_constituent_jet_ = true;
    }

    virtual void SetConstituentJet() const = 0;

    template<typename Multiplet_1_, typename Multiplet_2_>
    void SetJet(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2) const {
        jet_ = Join(multiplet_1, multiplet_2);
        has_jet_ = true;
    }

    virtual void SetJet() const = 0;

private:

    ClosestLepton closest_lepton_;

    mutable boca::Singlet constituent_jet_;

    mutable boca::Jet jet_;

    mutable bool has_constituent_jet_ = false;

    mutable bool has_jet_ = false;

};

}
