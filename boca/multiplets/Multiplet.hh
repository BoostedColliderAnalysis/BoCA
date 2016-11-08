/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Singlet.hh"
#include "boca/fastjet/Particle.hh"
#include "boca/multiplets/ClosestLepton.hh"
#include "boca/fastjet/SubJettiness.hh"
#include "boca/event/EventShapes.hh"

namespace boca
{

/**
* @ingroup Multiplets
* @brief %Multiplet base class
*
* capable of returning effective jets
*/
class Multiplet : public Identification
{

    template<typename Multiplet_>
    using NotJet = typename std::enable_if < !std::is_same<Multiplet_, boca::Jet>::value && !std::is_same<Multiplet_, boca::PseudoJet>::value && !std::is_same<Multiplet_, boca::Particle>::value >::type;

public:

    void SetClosestLepton(std::vector<boca::Lepton> const &leptons);

    ClosestLepton Lepton() const;

    boca::Jet Jet() const;

    boca::Mass Mass() const;

    Momentum Pt() const;

    /**
    * @name Angle related accessors
    * @{
    */

    /**
    * @brief Rapidity \f$y\f$
    */
    Angle Rap() const;

    /**
    * @brief Azimuth \f$\phi\f$
    */
    Angle Phi() const;

    /**
    * @brief Difference \f$\Delta \phi\f$ to a jet constrained to \f$[-\pi,\pi]\f$
    */
    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaPhiTo(Multiplet_ const &multiplet) const
    {
        return Jet().DeltaPhiTo(multiplet.Jet());
    }
    Angle DeltaPhiTo(PseudoJet const &jet) const;

    /**
    * @brief Difference \f$\Delta y\f$ to a jet
    */
    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaRapTo(Multiplet_ const &multiplet) const
    {
        return Jet().DeltaRapTo(multiplet.Jet());
    }
    Angle DeltaRapTo(PseudoJet const &jet) const;

    /**
    * @brief Distance \f$\Delta R\f$ to a jet
    */
    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Angle DeltaRTo(Multiplet_ const &multiplet) const
    {
        return Jet().DeltaRTo(multiplet.Jet());
    }
    Angle DeltaRTo(PseudoJet const &jet) const;

    /**
    * @brief Angular distance to a jet
    */
    template <typename Multiplet_, typename = NotJet<Multiplet_>>
    Vector2<Angle> DeltaTo(Multiplet_ const &multiplet) const
    {
        return Jet().DeltaTo(multiplet.Jet());
    }
    Vector2<Angle> DeltaTo(PseudoJet const &jet) const;

    /**
    * @brief Vector of rapidity \f$y\f$ and azimuth \f$\phi\f$
    * @param wrap_phi use the given \f$[-\pi,\pi]\f$ or wrap it by \f$2 \pi\f$
    */
    Vector2<Angle> Angles(bool wrap_phi = false) const;

    /**
    * @brief Vector of rapidity \f$y\f$ and azimuth \f$\phi\f$ with minimal distance to jet
    */
    template <typename Multiplet_/*, typename = NotJet<Multiplet_>*/>
    Vector2<Angle> AnglesMinTo(Multiplet_ const &multiplet) const
    {
        return Jet().AnglesMinTo(multiplet.Jet());
    }
    Vector2<Angle> AnglesMinTo(PseudoJet const& jet) const;
    //@}

    /**
    * @name SubStructure
    * @{
    */

    /**
    * @brief Jet of all constituents
    */
    boca::Singlet ConstituentJet() const;

    /**
    * @brief Weather the jet as constituetns
    */
    bool HasConstituents() const;

    /**
    * @brief All constituents
    */
    std::vector<boca::Jet> Constituents() const;

    /**
    * @brief Sub-jettiness
    */
    boca::SubJettiness SubJettiness() const;
    //@}

    void SetExtraInfo(double extra_info) {
        extra_info_ = extra_info;
    }

    double ExtraInfo() const {
        return extra_info_;
    }

protected:

    virtual Singlet GetConstituentJet() const = 0;

    virtual boca::Jet GetJet() const = 0;

    virtual std::vector<boca::Jet> Jets() const = 0;

    virtual std::vector<LorentzVector<Momentum>> LorentzVectors() const = 0;

    Mutable<boca::EventShapes> event_shapes_;

private:

    ClosestLepton closest_lepton_;

    Mutable<boca::Singlet> constituent_jet_;

    Mutable<boca::Jet> jet_;

    double extra_info_;

};

}
