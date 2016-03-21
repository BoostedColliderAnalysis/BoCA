/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Singlet.hh"
#include "SubJettiness.hh"
#include "ClosestLepton.hh"
#include "Particle.hh"

namespace boca
{

class Multiplet : public Identification
{

public:

    void SetClosestLepton(std::vector<boca::Lepton> const& leptons);

    ClosestLepton Lepton() const;

    boca::Singlet ConstituentJet() const;

    boca::Jet Jet() const;

    boca::Mass Mass() const;

    Momentum Pt() const;

    Angle Rap() const;

    Angle Phi() const;

    Vector2<Angle> Angles() const;

    Vector2<Angle> Angles(Vector2<Angle> const& angles) const;

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

    bool HasConstituents() const;

    boca::SubJettiness SubJettiness() const;

protected:

    virtual Singlet GetConstituentJet() const = 0;

    virtual boca::Jet GetJet() const = 0;

private:

    ClosestLepton closest_lepton_;

    Mutable<boca::Singlet> constituent_jet_;

    Mutable<boca::Jet> jet_;

};

template<typename Multiplet_1_, typename Multiplet_2_>
Jet Join(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    return Join(multiplet_1.Jet(), multiplet_2.Jet());
}

template<typename Multiplet_>
Jet Join(Jet const& jet, Multiplet_ const& multiplet)
{
    return Join(jet, multiplet.Jet());
}

template<typename Multiplet_>
Jet Join(Multiplet_ const& multiplet, Jet const& jet)
{
    return Join(jet, multiplet.Jet());
}

template<typename Multiplet_1_, typename Multiplet_2_>
boca::Singlet JoinConstituents(Multiplet_1_ const& multiplet_1, Multiplet_2_ const& multiplet_2)
{
    auto constituents = SortedByPt(Combine(multiplet_1.ConstituentJet().Constituents(), multiplet_2.ConstituentJet().Constituents()));
    boost::erase(constituents, boost::unique<boost::return_next_end>(constituents));
    return Join(constituents);
}

}
